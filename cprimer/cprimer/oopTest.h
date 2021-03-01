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

 
#endif
