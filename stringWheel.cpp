#include<iostream>
#pragma warning(disable:4996)

namespace stringwheel {
	class string {
	public:
		string() {
			m_data = new char[1];
			m_data = '\0';
			uiSize = 0;
		}

		string(char* str) {
			if (str == NULL) {
				m_data = new char[1];
				m_data = '\0';
				uiSize = 0;
			}
			else {
				uiSize = strlen(str);
				m_data = new char[uiSize+1];
				strcpy(m_data,str);
			}
		}

		int size() {
			return uiSize;
		}

		~string() {
			delete[] m_data;
		}

		string(const string& other) {
			uiSize = other.uiSize;
			m_data = new char[uiSize +1];
			strcpy(m_data,other.m_data);// \0为结束符
		}

		string& operator=(const string& other) {
			if (m_data == other.m_data) {
				return *this;
			}
			delete m_data;
			uiSize = strlen(other.m_data);
			m_data = new char[uiSize+1];
			strcpy(m_data,other.m_data);// \0结尾
			return *this;
		}

	private:
		unsigned int uiSize;
		char* m_data;

	};

}


int main12() {
	using namespace stringwheel;
	char cr[20] = "this is football";
	string str(cr);
	std::cout << str.size() << std::endl;
	return 12;
}



