#include<queue>
#include<mutex>
#include<condition_variable>
#include<chrono>
#include<iostream>

namespace BlockQueueWheel {

	template<typename T>
	class BlockQueue {
	public:
		//这里的定义必须在前面，不能放在后面
		using value_type= T;
		using container_type=std::queue<value_type>;
		using size_type=typename container_type::size_type;

	public:
		BlockQueue() = delete;
		BlockQueue(const size_type cap) :capacity(cap) {};
		BlockQueue(const BlockQueue& other) = default;
		BlockQueue(BlockQueue&& other) = default;
		BlockQueue& operator=(BlockQueue& other) = default;
		BlockQueue& operator=(BlockQueue&& other) = default;

	public:
		void put(const value_type& item ) {
			std::unique_lock<std::mutex> lock(mutex_);
			while (full()) {
				not_full.wait(lock);
			}
			container.push(item);
			not_empty.notify_one();
		}

		void take(value_type& out) {
			std::unique_lock<std::mutex> lock(mutex_);
			while (empty()) {
				not_empty.wait(lock);
			}
			out = container.front();
			container.pop();
			not_full.notify_one();
			
		}

		template<typename Duration>
		bool put_for(const value_type& in, const Duration& d) {
			std::unique_lock<std::mutex> lock(mutex_);
			if (not_full.wait_for(lock, d, [&](){ return not full();})) {
				container.push_back(in);
				not_empty.notify_one();
				return true;
			}
			else {
				return false;
			}
		}

		template<typename Duration>
		bool take_for(value_type& out, const Duration& d) {
			std::unique_lock<std::mutex> lock(mutex_);
			if (not_empty.wait_for(lock, d, [&]() {return not empty(); })) {
				out = container.front();
				container.pop();
				not_full.notify_one();
				return true;
			}
			else {
				return false;
			}
		}

	private:
		bool empty() const { return container.empty(); }
		bool full() const { return not(container.size() < capacity); }

	

	private:
		size_type capacity;
		container_type container;
		mutable std::mutex mutex_;
		mutable std::condition_variable not_full;
		mutable std::condition_variable not_empty;
	};
}

BlockQueueWheel::BlockQueue<int> iqueue(20);

void takeThread() {
	std::cout << "take int now ..." << std::endl;
	int out=0;
	//iqueue.take(out);
	auto a = std::chrono::seconds(5);
	std::cout << "wait for 5 sec now ..." << std::endl;
	std::cout << out << std::endl;
}

void putThread() {
	
	std::cout << "put int now ..." << std::endl;
	//iqueue.put(3);
}

int main22() {
	std::thread th1(takeThread);

	std::thread th2(putThread);

	th1.join();
	th2.join();
	return 1;
}












