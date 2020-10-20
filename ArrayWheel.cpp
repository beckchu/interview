#include<iostream>
#include<cstring>

using namespace std;

namespace ArrayWheel {
	template<typename T> class Array {
	public:
		Array(unsigned int val) :isize(val), iused(0),cap(NULL) {
			cap = (T*)malloc(sizeof(T) * isize);
		}

		~Array() {
			free(cap);
		}

		bool insert(T val) {
			if (iused < isize) {
				cap[iused++] = val;
			}
			else {
				T* pTemp = (T*)malloc(sizeof(T) * isize * 2);
				if (pTemp == NULL) return false;
				memmove(pTemp, cap, iused * sizeof(T));
				isize *= 2;
				cap = pTemp;
				cap[iused++] = val;
			}
			return true;
		}

		bool del(unsigned index) {
			if (index > iused + 1) return false;
			memmove(cap + index, cap + index + 1, sizeof(T) * (iused - index - 1));
			iused--;
			return true;
		}

		T randomVisit(unsigned int index) {
			try {
				return cap[index];
			}
			catch (...) {
				throw "Array is out of range...";
			}
		}

	private:
		unsigned int isize;
		unsigned int iused;
		T* cap;
	};
}



int main3() {
	ArrayWheel::Array<int> array(10);
	array.insert(10);
	array.insert(3);
	cout << array.randomVisit(0) << endl;
	return 0;
}











