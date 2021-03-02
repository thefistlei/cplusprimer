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
		virtual ~Quote() = default;	//�������������ж�̬��
	private:
		std::string bookNo;		//�鼮�� ISBN ���
	protected:
		double price = 0.0;		//��ʾ��ͨ״̬�²����۵ļ۸�
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
		Quote* itemP = &bulk;  //��ȷ����̬������Bulk_quote�������и�

		//Bulk_quote* bulkP = itemP;  //���󣬲��ܽ�����ת����������
	}

    void test1() { 
		Quote item;				// �������
		Bulk_quote bulk;		// ���������
		Quote* p = &item;		// pָ����� Quote ����
		p = &bulk;		        // pָ�������� Bulk_quote ����Ļ��ಿ��
		Quote& r = bulk;	    // r�󶨵������� Bulk_quote ����Ļ��ಿ��
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
		int prot_mem;  //protected ��Ա

	};
	class Sneaky :public Base {
	public:
		void clobber(Sneaky&);  //�ܷ���Sneaky::prot_mem

		void clobber(Base&);  //���ܷ���Base::prot_mem

		void testFunc();
		int j;
	};
	void Sneaky::clobber(Sneaky& s) {
		s.j = s.prot_mem = 0;
	} //��ȷ�ܷ���Sneaky�����private��protected��Ա

	void Sneaky::clobber(Base& b) {
		//b.prot_mem = 0; 
	}//�����ܷ���protected�ĳ�Ա

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
	//	int prot_mem;  //protected ��Ա

	//};
	//class Sneaky :public Base {
	//public:
	//	void clobber(Sneaky&);  //�ܷ���Sneaky::prot_mem

	//	void clobber(Base&);  //���ܷ���Base::prot_mem

	//	void testFunc();
	//	int j;
	//};
	//void Sneaky::clobber(Sneaky& s) { 
	//	s.j = s.prot_mem = 0;
	//} //��ȷ�ܷ���Sneaky�����private��protected��Ա

	//void Sneaky::clobber(Base& b) { 
	//	//b.prot_mem = 0; 
	//}//�����ܷ���protected�ĳ�Ա

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
		//char g() {return priv_mem;} //error:�����private���޷�����
	};

	struct Priv_Derv : private Base2
	{
		//˽�м̳в�Ӱ���������еķ��ʣ�ֻ��Base����Priv_Derv��˵����private��
		int f() const { return prot_mem; }
	};

	void fun1()
	{
		Pub_Derv d1;
		Priv_Derv d2;
		d1.pub_mem();
		//d2.pub_mem();   //error:������˽�м̳У�����Priv_Derv��˵Base2������඼��private���͵�
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
		int prot_mem;  //protected ��Ա 
	private:
		int priv_mem;
	};

	class Sneaky :public Base {
		friend void clobber(Sneaky&);  //�ܷ���Sneaky::prot_mem 
		friend void clobber(Base&);  //���ܷ���Base::prot_mem 
		int j;
	};


	class Pal
	{
	public:
		 int f(Base b) { return b.prot_mem; }
		// int f2(Sneaky s) {return s.j;}  //error:Pal ����Sneaky����Ԫ
		int f3(Sneaky s) { return s.prot_mem; }    //��Ҫ���ȣ����ǶԵ�
		int f4(Sneaky s) { return s.priv_mem; }    //��Ҫ���ȣ����ǶԵ�
	};

	class D2 : public Pal
	{
	public:
		// int mem(Base b){return b.prot_mem;}    //error: ��Ԫ���޷��̳е�

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
		using Base::size;  //���ֶ���ߴ���صĳ�Ա�ķ��ʼ���

	protected:
		//using Base::n; //ʹ��using�ؼ��ָı��Ա�����ķ��ʼ���

	}; 

	Derived d;
	std::size_t t1 = d.size();//ok
	//std::size_t t2 = d.n;//error
}

#endif
