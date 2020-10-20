#include<cstdlib>
#include<vector>

/*#define offsetof(TYPE,MEMBER) ({(long long)&((TYPE*)0)->MEMBER})
#define container(PTR,TYPE,MEMBER) ({\
	const typeof((TYPE*)0->MEMBER)* __mptr=(PTR);\
	(TYPE*)((char*)__mptr - offsetof(TYPE,MEMBER));})*/

namespace {

	typedef struct node_{
	public:
		node_(int k,int v,int num):key(k),value(v),maxlevel(num) {
			next.resize(maxlevel);
		}
		~node_() = default;

	public:
		int key;
		int value;
		int maxlevel;
		std::vector<node_*> next;
		//node_* next[0];

	}listnode;

	class skipList {
	public:
		skipList():level(1),count(0) {
			head = new listnode(0,0,1);
		}

		~skipList() {
			while (head) {
				listnode* node = head;
				head = head->next[0];
				delete node;
			}
		}

		int insert(int key,int value) {
			listnode* prev = head;
			listnode* temp = NULL;
			std::vector<listnode*> update(this->level);
			for (int i = this->level - 1; i >= 0; i--) {
				while ((temp = prev->next[i])!=NULL && temp->key < key) {
					prev = temp;
				}
				update[i] = prev;
			}
			if (temp != NULL && temp->key == key) {
				return 3;
			}
			int ilevel = skipListLevel();
			listnode* node = new listnode(key,value,ilevel);
			if (ilevel > this->level) {
				for (int i = this->level; i < ilevel; i++) {
					if (i == update.size()) update.emplace_back();
					update[i] = head;
				}
				this->level = ilevel;
			}
			for (int i = 0; i < this->level; i++) {
				node->next[i] = update[i]->next[i];
				update[i]->next[i] = node;
			}
			this->count++;
			return true;
		}

	int del(int key) {
		listnode* prev = head;
		listnode* temp = NULL;
		std::vector<listnode*> update(level);
		for (int i = this->level - 1; i >= 0; i--) {
			while ((temp = prev->next[i]) != NULL && temp->key < key) {
				prev = temp;
			}
			update[i] = prev;
		}
		if (temp != NULL && temp->key == key) {
			for (int i = 0; i < this->level; i++) {
				update[i]->next[i] = temp->next[i];
			}
			delete temp;
			for (int i = this->level - 1; i >= 0; i--) {
				if (head->next[i] == NULL) {
					this->level--;
				}
				else {
					break;
				}
			}
			this->count--;
		}
		else {
			return 3;
		}
	}

	int search(int key) {
		if (head->next[0] == NULL) return 1;
		listnode* temp;
		listnode* prev = head;
		for (int i = 0; i < this->level; i++) {
			while ((temp = prev->next[i]) != NULL && temp->key <= key) {
				if (temp->key == key) {
					return temp->value;
				}
				prev = temp;
			}
		}
		return -1;
	}

	private:
		int skipListLevel() {
			int level = 0;
			for (int i = 0; i < this->level; i++) {
				if (rand() % 2 == 0) {
					level++;
				}
			}
			return level ? level:1;
		}
	private:
		int count;
		int level;//现在的层数
		listnode* head;
	};
}


int main() {
	skipList list;
	list.insert(2,8);
	list.insert(3,5);
	list.insert(4, 5);
	list.insert(5, 5);

}



