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

 
#endif
