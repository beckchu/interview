#include<iostream>

using namespace std;

namespace DlistWheel {

	struct stDlist {
		int data;
		stDlist* prev;
		stDlist* next;
	};

class Dlist {
public:
	Dlist():isize(0),head(NULL),tail(NULL) {
		//head和tail中间夹着真实的数据
		head = new stDlist();
		tail = new stDlist();
		head->prev = NULL;
		head->next = tail;
		tail->prev = head;
		tail->next = NULL;
	}

	~Dlist() {
		while (head) {
			stDlist* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void dump() {
		stDlist* temp = head->next;
		while (temp != tail) {
			cout << temp->data << endl;
			temp = temp->next;
		}
	}

	bool insert_front(int val) {
		stDlist* node = new stDlist();
		stDlist* next = head->next;
		
		head->next = node;
		node->prev = head;
		node->next = next;
		next->prev = node;
	}

	bool insert_back(int val) {

		stDlist* node = new stDlist();
		stDlist* prev = tail->prev;
		node->next = tail;
		tail->prev = node;

		node->prev=prev;
		prev->next=node;
		return true;
	}

	bool insert(stDlist* prev, int val) {
		if (prev == NULL) {
			return false;
		}
		stDlist* temp = head;
		while (temp!=NULL && temp!=prev) {
			temp = temp->next;
		}
		if (temp == NULL) return false;
		temp = prev->next;
		stDlist* node=new stDlist();
		node->data = val;
		prev->next = node;
		node->prev = prev;
		node->next = temp;
		temp->prev = node;
		return true;
	}

private:
	unsigned int isize;
	stDlist* head;
	stDlist* tail;

};

}

using namespace DlistWheel;

