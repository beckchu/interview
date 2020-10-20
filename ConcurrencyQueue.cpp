#include<condition_variable>
#include<mutex>
#include<queue>
#include<vector>
#include<iostream>


namespace ConcurrencyQueueWheel {
template<typename T>
class ConcurrencyQueue {
public:
	using value_type=T;
	using container_type=std::queue<value_type>;
	using container_size_type=typename container_type::size_type;
public:
	ConcurrencyQueue() = delete;
	ConcurrencyQueue(container_size_type isize):size(isize){}
	ConcurrencyQueue(const ConcurrencyQueue& other) = default;
	ConcurrencyQueue(ConcurrencyQueue&& other) = default;
	ConcurrencyQueue& operator=(const ConcurrencyQueue& other) = default;
	ConcurrencyQueue& operator=(ConcurrencyQueue&& other) = default;

	bool is_empty() {
		std::unique_lock<std::mutex> lock(mutex_);
		return container_.empty();
	}

	void push(value_type item) {
		std::unique_lock<std::mutex> lock(mutex_);
		container_.push(std::move(item));
		condition_.notify_one();
	}

	void waitAndPop(value_type& out) {
		std::unique_lock<std::mutex> lock(mutex_);
		while (empty_()) {
			condition_.wait(lock);
		}
		out = std::move(container_.front());
		container_.pop();
	}

	std::shared_ptr<value_type>  waitAndPop() {
		std::unique_lock<std::mutex> lock(mutex_);
		while (empty_()) {
			condition_.wait(lock);
		}
		auto out = std::make_shared<value_type>(std::move(container_.front()));
		container_.pop();
		return out;
	}

	bool TryPop(value_type& out) {
		std::unique_lock<std::mutex> lock(mutex_);
		if (empty_) {
			return false;
		}
		else {
			out = std::move(container_.front());
			container_.pop();
			return true;
		}
	}

	std::shared_ptr<value_type> TryPop() {
		std::unique_lock<std::mutex> lock(mutex_);
		if (empty_) {
			return nullptr;
		}
		else {
			auto out = std::move(container_.front());
			container_.pop();
			return out;
		}
	}

private:
	bool empty_() {
		return container_.empty();
	}

private:
	container_type container_;
	container_size_type size;
	std::mutex mutex_;
	std::condition_variable condition_;
};

}
int a = 21;
ConcurrencyQueueWheel::ConcurrencyQueue<std::vector<int>> q(a);

void thread1() {
	std::vector<int> iv = {1,2,4,5};
	std::cout << "push vector iv now ..." << std::endl;
	q.push(iv);
	std::vector<int> iv1 = { 2,4,5,7 };
	//q.push(iv1);
}

void thread2() {

	std::vector<int> iv;
	q.waitAndPop(iv);
	std::cout << iv[1] << std::endl;
	q.waitAndPop(iv);
	std::cout << iv[1] << std::endl;
}

int main12121() {
	std::thread th1(thread1);
	std::thread th2(thread2);

	th1.join();
	th2.join();
	system("pause");
	return 0;
}

