/*
 * 
*/
#ifndef OOPTEST_H
#define OOPTEST_H

//#include "Version_test.h"

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

#include <functional>
 
#include <istream>
#include <ostream>


using std::cout;

#include <iostream>
using std::cin; using std::cout; using std::endl;


#include <iostream> 
#include <fstream>
#include <sstream> 



// forward declaration needed for friend declaration in StrBlobTest
namespace oopTest
{  
	class Quote {
	public:
		Quote() = default;
		Quote(const std::string& book, double sales_price) :
			bookNo(book), price(sales_price) {}
		std::string isbn() const { return bookNo; }
		virtual double net_price(std::size_t n) const
		{
			return n * price;
		}
		virtual ~Quote() = default;	//对析构函数进行动态绑定
	private:
		std::string bookNo;		//书籍的 ISBN 编号
	protected:
		double price = 0.0;		//表示普通状态下不打折的价格
	};

	class Bulk_quote : public Quote
	{
	public:
		Bulk_quote() = default;
		Bulk_quote(const std::string&, double, std::size_t, double);
		double net_price(std::size_t) const override {
			return discount;
		};
	private:
		std::size_t min_qty = 0;
		double discount = 0;
	};

	void test3() {
		struct A
		{ 
			void f1(int a, int b = 0) const {
				std::cout << "a f1" << endl;
			}
		};
		struct B : A
		{
			void f1(int a, int b = 2) const {
				std::cout << "b f1" << endl;
			}
		};

		A a;
		B b;
		a.f1(1);
		b.f1(1);

		A* pa = &b;   
		pa->f1(1);
	}


	void test2() {
		Bulk_quote bulk;
		Quote* itemP = &bulk;  //正确；动态类型是Bulk_quote，发生切割

		//Bulk_quote* bulkP = itemP;  //错误，不能将基类转换成派生类
	}

    void test1() { 
		Quote item;				// 基类对象
		Bulk_quote bulk;		// 派生类对象
		Quote* p = &item;		// p指向基类 Quote 对象
		p = &bulk;		        // p指向派生类 Bulk_quote 对象的基类部分
		Quote& r = bulk;	    // r绑定到派生类 Bulk_quote 对象的基类部分
    } 

	void test() {
		test1();
		test2();
		test3();
	}

	
}

namespace oopPermissionTest0
{
	class Base {
	protected:
		int prot_mem;  //protected 成员

	};
	class Sneaky :public Base {
	public:
		void clobber(Sneaky&);  //能访问Sneaky::prot_mem

		void clobber(Base&);  //不能访问Base::prot_mem

		void testFunc();
		int j;
	};
	void Sneaky::clobber(Sneaky& s) {
		s.j = s.prot_mem = 0;
	} //正确能访问Sneaky对象的private和protected成员

	void Sneaky::clobber(Base& b) {
		//b.prot_mem = 0; 
	}//错误不能访问protected的成员

	void Sneaky::testFunc() {
		std::cout << prot_mem;
		;
	}

	void test() {
		Sneaky o;
		o.testFunc();
	}

	//class Base {
	//protected:
	//	int prot_mem;  //protected 成员

	//};
	//class Sneaky :public Base {
	//public:
	//	void clobber(Sneaky&);  //能访问Sneaky::prot_mem

	//	void clobber(Base&);  //不能访问Base::prot_mem

	//	void testFunc();
	//	int j;
	//};
	//void Sneaky::clobber(Sneaky& s) { 
	//	s.j = s.prot_mem = 0;
	//} //正确能访问Sneaky对象的private和protected成员

	//void Sneaky::clobber(Base& b) { 
	//	//b.prot_mem = 0; 
	//}//错误不能访问protected的成员

	//void Sneaky::testFunc() { 
	//	std::cout << prot_mem;
	//	;
	//}

	//void test() {
	//	Sneaky o;
	//	o.testFunc(); 
	//}
}

namespace oopPermissionTest
{
	//class permissionTest {
	//public:
	//	permissionTest() {}
	//	~permissionTest() {}

	//};

	class Base2
	{
	public:
		void pub_mem() {}
	protected:
		int prot_mem;
	private:
		char priv_mem;
	};

	struct Pub_Derv : public Base2
	{
		int f() { return prot_mem; }
		//char g() {return priv_mem;} //error:这个是private的无法访问
	};

	struct Priv_Derv : private Base2
	{
		//私有继承不影响派生类中的访问，只是Base对于Priv_Derv来说都是private的
		int f() const { return prot_mem; }
	};

	void fun1()
	{
		Pub_Derv d1;
		Priv_Derv d2;
		d1.pub_mem();
		//d2.pub_mem();   //error:这里是私有继承，对于Priv_Derv来说Base2里面的类都是private类型的
	}

	struct Derived_from_public : public Pub_Derv
	{
		int use_base() { return prot_mem; }    //ok:protected in pub_Derv
	};

	void test() {

	}
}

namespace oopPermissionTest2
{

	class Base {
		friend class Pal;
	protected:
		int prot_mem;  //protected 成员 
	private:
		int priv_mem;
	};

	class Sneaky :public Base {
		friend void clobber(Sneaky&);  //能访问Sneaky::prot_mem 
		friend void clobber(Base&);  //不能访问Base::prot_mem 
		int j;
	};


	class Pal
	{
	public:
		 int f(Base b) { return b.prot_mem; }
		// int f2(Sneaky s) {return s.j;}  //error:Pal 不是Sneaky的友元
		int f3(Sneaky s) { return s.prot_mem; }    //不要惊讶，这是对的
		int f4(Sneaky s) { return s.priv_mem; }    //不要惊讶，这是对的
	};

	class D2 : public Pal
	{
	public:
		// int mem(Base b){return b.prot_mem;}    //error: 友元是无法继承的

	};

	void test() {

	}
}

namespace oopPermissionTest3
{
	class Base {
	public:
		Base() {}
	public:
		std::size_t size() const { return n; }
	protected:
		std::size_t n;
	};

	class Derived : private Base {
	public:
		using Base::size;  //保持对象尺寸相关的成员的访问级别

	protected:
		//using Base::n; //使用using关键字改变成员变量的访问级别。

	}; 

	Derived d;
	std::size_t t1 = d.size();//ok
	//std::size_t t2 = d.n;//error
}

#endif
