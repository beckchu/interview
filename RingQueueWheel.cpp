#include<iostream>

namespace ringQueueWheel {

	class RingQueue{
	public:
		RingQueue(int isize):head(0),tail(0),size(isize) {
			m_data = new int[isize];
		}

		~RingQueue()
		{
			delete[] m_data;
		}

		int dequeue() {
			if (is_empty()) {
				return -1;
			}
			int data = m_data[head];
			head = (head + 1) % size;
		}

		bool enqueue(int data) {
			if (is_full()) {
				return false;
			}
			m_data[tail] = data;
			tail = (tail + 1) % size;
			return true;
		}

		int capacity() {
			return size;
		}


	private:
		int validIndex(int cur,int step) {
			return (cur + step) % size;
		}

		bool is_empty() {
			return head == tail;
		}

		bool is_full() {
			return (tail + 1) % size == head;
		}

		int head;
		int tail;
		int size;
		int* m_data;
	};

}

int main11() {
	using namespace ringQueueWheel;
	RingQueue queue(10);
	std::cout << queue.capacity() << std::endl;
	return 0;
}

