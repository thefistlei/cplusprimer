/*
 *  
*/ 
 

#ifndef TESTSALESITEM_H
// we're here only if SALESITEM_H has not yet been defined 
#define TESTSALESITEM_H

//#include "Version_test.h" 

// Definition of TestSales_item class and related functions goes here
#include <iostream>
#include <string>

class TestSales_item
{
public:
	TestSales_item(const std::string& book) :isbn(book), units_sold(0), revenue(0.0) {}
	TestSales_item(std::istream& is) { is >> *this; }
	friend std::istream& operator>>(std::istream& in, TestSales_item&);
	friend std::ostream& operator<<(std::ostream&, const TestSales_item&);
public:
	TestSales_item& operator+=(const TestSales_item&);
public:
	double avg_price() const;
	bool same_isbn(const TestSales_item& rhs)const
	{
		return isbn == rhs.isbn;
	}
	TestSales_item() :units_sold(0), revenue(0.0) {}
public:
	std::string isbn;
	unsigned units_sold;
	double revenue;
};

	using std::istream;
	using std::ostream;
	TestSales_item operator+(const TestSales_item&, const TestSales_item&);
	inline bool operator==(const TestSales_item& lhs, const TestSales_item& rhs)
	{
		return lhs.units_sold == rhs.units_sold && lhs.revenue == rhs.revenue && lhs.same_isbn(rhs);
	}
	inline bool operator!=(const TestSales_item& lhs, const TestSales_item& rhs)
	{
		return !(lhs == rhs);
	}

	inline TestSales_item& TestSales_item::operator +=(const TestSales_item& rhs)
	{
		units_sold += rhs.units_sold;
		revenue += rhs.revenue;
		return *this;
	}
	inline TestSales_item operator+(const TestSales_item& lhs, const TestSales_item& rhs)
	{
		TestSales_item ret(lhs);
		ret += rhs;
		return ret;
	}
	inline istream& operator>>(istream& in, TestSales_item& s)
	{
		double price;
		in >> s.isbn >> s.units_sold >> price;
		if (in)
			s.revenue = s.units_sold * price;
		else
			s = TestSales_item();
		return in;
	}
	inline ostream& operator<<(ostream& out, const TestSales_item& s)
	{
		out << s.isbn << "\t" << s.units_sold << "\t" << s.revenue << "\t" << s.avg_price();
		return out;
	}
	inline double TestSales_item::avg_price() const
	{
		if (units_sold)
			return revenue / units_sold;
		else
			return 0;
	}

 
/*
			void static iostream_TestSales_item() {
				istream_iterator<TestSales_item> in_iter(cin), eof;

				//创建一个ostream_iterator，输出元素类型是TestSales_item，关联到流cout，且每次输出时候在末尾加上"\n"
				ostream_iterator<TestSales_item> out_iter(cout, "\n");

				//创建TestSales_item对象sum，并且用in_iter内的元素初始化，接着in_iter读取下一个值
				TestSales_item sum = *in_iter++;

				//创建while循环，当in_iter关联的流没有遇到错误，并且没有到达文件末尾的时候，循环继续
				while (in_iter != eof)
				{
					//如果刚才读取的元素的isbn和sum中的Sales_data的isbn相等，那么把这个元素加到sum中，且
					//in_iter读取下一个值
					if (in_iter->isbn == sum.isbn)
					{
						//sum += *in_iter++;
					}
					//如果新读取的对象的isbn不等于sum中元素的isbn，那先输出sum中的对象，然后把新*in_iter
					//赋值给sum，然后in_iter再读取下一个值
					else
					{
						*out_iter++ = sum;
						sum = *in_iter++;
					}
				}
			}
 */
#endif
