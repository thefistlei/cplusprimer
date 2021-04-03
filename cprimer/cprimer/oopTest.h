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

namespace oopClassDomainTest
{
	class Quote {
	};
	 
	class Disc_quote : public Quote {
	public:
		Disc_quote() {};
		void discount_policy()   {  
		}  
	};

	class Bulk_quote : public Disc_quote {
	};



	void test() {
		Bulk_quote bulk;
		Bulk_quote* bulkP = &bulk;//��̬���ͺͶ�̬����һ��
		Quote* itemP = &bulk;//��̬���ͺͶ�̬���Ͳ�һ��
		bulkP->discount_policy(); //ok
		//itemP->discount_policy();//error
	} 
}

namespace oopClassDomainTest2
{
	struct Base {
		Base() : mem(0) { }
	protected:
		int mem;
	};

	struct Derived : Base {
		Derived(int i) : mem(i) { } // initializes Derived::mem to i
								   // Base::mem is default initialized
		int get_mem() { return mem; }  // returns Derived::mem
		int get_base_mem() { return Base::mem; }
		// . . .
	protected:
		int mem;   // hides mem in the base
	};



	void test() {
		Derived d(42);
		cout << d.get_mem() << endl;       // prints 42
		cout << d.get_base_mem() << endl;  // prints 0
	}
}

namespace oopClassDomainTest3
{
	struct Base { 
		int memfcn() { return 1; };
	};

	struct Derived : Base {
		int memfcn(int) { return 1; };// hides mem in the base 
	};
	 
	void test() {
		Derived d;
		Base b;
		b.memfcn();
		d.memfcn(10);
		//d.memfcn();//error
		d.Base::memfcn();//ok 
	}
}

namespace oopClassDomainTest4
{
	class Base {
	public:
		virtual int fcn();
	};
	 
	class D1 : public Base {
	public:
		// hides fcn in the base; this fcn is not virtual
		// D1 inherits the definition of Base::fcn() 
		int fcn(int);      // parameter list differs from fcn in Base
		virtual void f2(); // new virtual function that does not exist in Base
	};
	 
	class D2 final : public D1 {
	public:
		int fcn(int); // nonvirtual function hides D1::fcn(int)
		int fcn();    // overrides virtual fcn from Base
		void f2();    // overrides virtual f2 from D1
	};
	 
	int Base::fcn() {
		cout << "Base::fcn()" << endl; return 0;
	}

	int D1::fcn(int) {
		cout << "D1::fcn(int)" << endl;
		return 0;
	}
	void D1::f2() {
		cout << "D1::f2()" << endl;
	}

	int D2::fcn(int) {
		cout << "D2::fcn(int)" << endl;
		return 0;
	}
	int D2::fcn() { 
		cout << "D2::fcn()" << endl; 
		return 0; 
	}

	void D2::f2() 	{ 
		cout << "D2::f2()" << endl;
	}

	void test()
	{
		D1 dobj, * dp = &dobj;
		dp->fcn(42); // ok: static call to D1::fcn(int)

		Base bobj;  D1 d1obj; D2 d2obj;

		Base* bp1 = &bobj, * bp2 = &d1obj, * bp3 = &d2obj;
		bp1->fcn(); // �����, Base::fcn  
		bp2->fcn(); // �����, Base::fcn at run time
		bp3->fcn(); // �����, D2::fcn at run time

		D1* d1p = &d1obj; D2* d2p = &d2obj;
		d1p->f2(); // �����, will call D1::f2() at run time
		d2p->f2(); // �����, will call D2::f2() at run time

		D1* p2 = &d2obj; D2* p3 = &d2obj;
		p2->fcn(42);  // statically bound, calls D1::fcn(int)
		p3->fcn(42);  // statically bound, calls D2::fcn(int)

		D1* dp1 = &d2obj; D2* dp2 = &d2obj;
		dp1->fcn(10); // static call to D1::fcn(int)
		dp2->fcn(10); // static call to D2::fcn(int)
	}
}

namespace oopClassDomainTest_copydes
{
	class B {
	public:
		B() {};
		B(const B&) = delete;
	};

	class D : public B{ 
	}; 
	 
	void test()
	{
		D d;//ok
		//D d2(d);//error
		//D d3(std::move(d));//��ʽʹ��D�ı�ɾ���Ŀ������캯��
	}
}

namespace oopClassDomainTest_move
{
	class Quote
	{
	public:
		Quote() = default;
		Quote(const string& s, double sales_price) :bookNo(s), price(sales_price) {}
		Quote(const Quote&);//�������캯��
		Quote& operator=(const Quote&);//������ֵ�����
		Quote(Quote&&);//�ƶ����캯��
		Quote& operator=(Quote&&);//�ƶ���ֵ����
		string isbn() const;
		virtual double net_price(size_t n) const;//�麯��
		virtual void debug() const;
		virtual ~Quote() {}//�������������ж�̬��

	private:
		string bookNo;
	protected:
		double price = 0.0;
	};
 
	ostream& print_total(ostream& os, const Quote& item, size_t n)
	{
		double ret = item.net_price(n);
		os << "ISBN��" << item.isbn()
			<< " #sold: " << n << " total due: " << ret << endl;
		item.debug();
		return os;
	}
	string Quote::isbn() const
	{
		return bookNo;
	}

	double Quote::net_price(size_t n) const
	{
		return n * price;
	}

	void Quote::debug() const
	{
		cout << "i am quote:" << bookNo << " " << price << endl;
	}

	Quote::Quote(const Quote& q)
	{
		cout << "hello i am �������캯��Quote" << endl;
		bookNo = q.bookNo;
		price = q.price;
	}

	Quote& Quote::operator=(const Quote& q)
	{
		cout << "hello i am ������ֵ�����Quote" << endl;
		if (this != &q)
		{
			bookNo = q.bookNo;
			price = q.price;
		}
		return *this;
	}

	Quote::Quote(Quote&& q)
	{
		cout << "hello i am �ƶ����캯��Quote" << endl;
		bookNo = std::move(q.bookNo);
		price = std::move(q.price);
		q.bookNo = "";
		q.price = 0;
	}

	Quote& Quote::operator=(Quote&& q)
	{
		cout << "hello i am �ƶ���ֵ�����Quote" << endl;
		if (this != &q)
		{
			bookNo = std::move(q.bookNo);
			price = std::move(q.price);
			q.bookNo = "";
			q.price = 0;
		}
		return *this;
	}

	void test() {
		Quote test("cuinan", 100);
		Quote test1(test);
		Quote test2;
		test2 = test;
		Quote test3(std::move(test));
		test2 = std::move(test);
	}
} 

namespace oopDeriveClass_copy
{
	class Base { /* ... */ };
	class D : public Base
	{
	public:
		// by default, the base class default constructor initializes the base part of an object
		// to use the copy or move constructor, we must explicitly call that
		// constructor in the constructor initializer list
		D(const D& d) : Base(d)   // copy the base members
			/* initializers for members of D */ { /* ... */
		}

		D(D&& d) : Base(std::move(d))    // move the base members
			/* initializers for members of D */ { /* ... */
		}
	};
	 
}
#endif
