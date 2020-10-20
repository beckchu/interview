#include<iostream>


namespace ListStackWheel {
	struct stlistnode {
		int data;
		stlistnode* next;
	};


	class ListStack {
	public:
		ListStack() {
			head = new stlistnode();
			head->next = NULL;
		}

		~ListStack() {
			while (head) {
				stlistnode* temp = head;
				head = head->next;
				delete temp;
			}
		}

		bool push(int data) {
			stlistnode* node = new stlistnode();
			node->data = data;
			node->next = NULL;
			stlistnode* next = head->next;
			head->next = node;
			node->next = next;
			return true;
		}

		int top() {
			if (isEmpty()) {
				return -1;
			}
			return head->next->data;
		}

		bool pop() {
			if (isEmpty()) {
				return false;
			}
			stlistnode* top = head->next;
			head->next = top->next;
			delete top;
			return true;
		}

		void dump() {
			if (isEmpty()) {
				std::cout << "is empty now..." << std::endl;
			}
			stlistnode* cur;
			cur = head->next;
			while (cur) {
				std::cout << cur->data<< std::endl;
				cur = cur->next;
			}
			std::cout << "this is end..." << std::endl;
		}

	private:
		bool isEmpty() {
			return head->next == NULL;
		}

	private:
		stlistnode* head;
	};


}


int main97987() {

	ListStackWheel::ListStack st;
	st.push(19);
	st.push(10);
	
	st.dump();
	st.pop();
	st.pop();
	std::cout << st.top() << std::endl;
	st.pop();
	system("pause");
	return 0;
}
