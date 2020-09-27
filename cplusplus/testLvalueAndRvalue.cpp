/*
brief:对右值的总结
*/

#include<vector>
#include<string>
#include<iostream>

using namespace std;

//完美转发应用
void fun(int& x) { cout << "call lvalue ref" << endl; }
void fun(int&& x) { cout << "call rvalue ref" << endl; }
void fun(const int& x) { cout << "call const lvalue ref" << endl; }
void fun(const int&& x) { cout << "call const rvalue ref" << endl; }

template<typename T>
void PerfectForward(T&& t) {
	cout << "T is a ref type?: " << is_reference<T>::value << endl;
	cout << "T is a lvalue ref type?: " << is_lvalue_reference<T>::value << endl;
	cout << "T is a rvalue ref type?: " << is_rvalue_reference<T>::value << endl;
	fun(forward<T>(t));
}

//模板推倒,完美转发
void IrunCodeActually(int&& X) {

}

template<typename T>
void IamForwording(T&& t) {//模板推导根据实参，然后通过引用折叠
	IrunCodeActually(static_cast<T&&>(t));
}

/*
void IamForwording(X& && t) {//模板推导根据实参，然后通过引用折叠
	IrunCodeActually(static_cast<X& &&>(t));
}
//经过引用折叠
void IamForwording(X& t) {
	IrunCodeActually(static_cast<X&>(t));
}
//
void IamForwording(X&& && t) {//模板推导根据实参，然后通过引用折叠
	IrunCodeActually(static_cast<X& &&>(t));
}
//经过引用折叠
void IamForwording(X&& t) {
	IrunCodeActually(static_cast<X&&>(t));
}
//对于右值而言，当使用右值引用表达式引用的时候，右值引用确是一个不折不扣的左值
//我们想在函数调用中继续传递右值，要使用std::move将左值转换为右值
//std::move==static_cast==forward实际差别不大
*/

typedef const int T;
typedef T& TR;
typedef T&& TRR;

void judgeType() {
	cout << "lvalue_ref_type?: " << is_lvalue_reference<TR>::value << endl;
	cout << "rvalue_ref_type?: " << is_rvalue_reference<TR>::value << endl;

	cout << "lvalue_ref_type?: " << is_lvalue_reference<TR&>::value << endl;
	cout << "rvalue_ref_type?: " << is_rvalue_reference<TR&>::value << endl;

	cout << "lvalue_ref_type?: " << is_lvalue_reference<TR&&>::value << endl;
	cout << "rvalue_ref_type?: " << is_rvalue_reference<TR&&>::value << endl;

	cout << "lvalue_ref_type?: " << is_lvalue_reference<TRR>::value << endl;
	cout << "rvalue_ref_type?: " << is_rvalue_reference<TRR>::value << endl;

	cout << "lvalue_ref_type?: " << is_lvalue_reference<TRR&>::value << endl;
	cout << "rvalue_ref_type?: " << is_rvalue_reference<TRR&>::value << endl;

	cout << "lvalue_ref_type?: " << is_lvalue_reference<TRR&&>::value << endl;
	cout << "rvalue_ref_type?: " << is_rvalue_reference<TRR&&>::value << endl;
}

int main() {
	//lvalue是一种名字，有固定地址的表达式  rvalue是匿名，没有固定地址的对象；
	{
		int a = 10;				//a:lvalue 10:rvalue
		int* pFlag = &a;		//pFlag:lvalue &a:rvalue
		vector<int>vctTemp;		//vcTemp:lvalue
		vctTemp.push_back(2);	//1:rvalue
		string str1 = "hello";	//str1:lvalue hello:rvalue
		const int& m = 1;		//m:lvalue 1:rvalue
	}
	

	//对右值引用的效果：右值生命期被延长，但是是常量，满足不了更多的需求
	{
		int a = 100;
		int& b = a;
		const int& c = a;
		const int& d = 100;//为右值100的别名
		cout << "a=" << a << " b=" << b << " c=" << c << " d=" << d << endl;
		int x = 150;
		int y = 250;
		const int& i = x + y;//为右值x+y命名常量别名
		cout << "i = " << i << endl;
		//i += 100;// error ide直接给出错误提示
		//int& f = 10;//error 必须为常量引用
	}
	
	//经右值引用以后，右值就变为和左值一样持久的对象，引用定义中的名称就是这个普通对象的名称；
	{
		int&& a = 100;		//右值100的别名
		int b = 200;
		int&& c = a + b;	//右值a+b的命名别名
		int&& d = 300;		//右值300的命名别名
		a += 10;			//修改右值引用值
		int e = a;			//右值引用为左值赋值
		cout << "a = " << a << ", b= " << b << ", c= " << c << ", d = " << d << ", e=" << e << endl;
	}
	
	//转移语义：调用移动构造函数和移动赋值函数
	//转移函数：T&& move(T&) 左值转换为右值，
	/*{
		template<typename T> 
		void swap(T & a, T & b) {
			T temp = move(a);
			a = move(b);
			b = move(temp);
		}
	}*/

	//参数完美转发：参数传递过程中要保留左右值属性
	//引用折叠规则：
	/*
	typedef const int T;
	typedef T& TR;
	TR& v = 10;
	
	TR类型定义			声明v的类型定义			v的实际类型
	T&					TR						A&
	T&					TR&						A&
	T&					TR&&					A&
	T&&					TR						A&&
	T&&					TR&						A&
	T&&					TR&&					A&&
	*/
	//原则：一旦TR和v中出现了左值引用，引用折叠总是优先将其折叠为左值引用
	judgeType();
	
	//完美转发应用
	PerfectForward(10);//rvalue

	int a = 5;
	PerfectForward(a);//lvalue
	PerfectForward(move(a));//rvalue

	const int b = 8;
	PerfectForward(b);//const lvalue
	PerfectForward(move(b));//const rvalue将左值转换为右值进行调用

	return 0;

}

