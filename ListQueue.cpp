#include<iostream>
namespace listqueue {
	struct list_entry {
		int data;
		list_entry* next;
	};

	class ListQueue {
	public:
		ListQueue() :isize(0), head(NULL), tail(NULL) {
		}

		~ListQueue() {
			while (head != NULL) {
				list_entry* temp = head;
				head = head->next;
				delete temp;
			}
		}

		int pop_fornt() {
			if (is_empty()) return NULL;
			list_entry* temp = head;
			head = head->next;
			isize--;
			int i = temp->data;
			delete temp;
			return i;
		}

		bool push_back(int data) {
			list_entry* node = new list_entry();
			node->data = data;
			isize++;
			if (is_empty()) {
				head = node;
				tail = node;
			}
			else {
				tail->next = node;
				tail = node;
			}
			return true;
		}

		int size() {
			return isize;
		}

	private:
		bool is_empty() {
			return isize == 0;
		}

	private:
		list_entry* head;
		list_entry* tail;
		int isize;
	};
}
