// cprimer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include "add_Item.h" 

#include "useShareVariable1.h"
#include "useShareVariable2.h"
#include "stringTest.h"
#include "vectorTest.h"
#include "MyExecption.h"
#include "ioTest.h"
#include "orderContainer.h"
#include "genericAlgorithm.h"

#include "mapTest.h"
#include "smartPointer.h"
#include "referenceCount.h"
#include "referenceCountSwap.h"
#include "copyControl.h"

void testVariable() {
	float f1 = 4.4f;
	float f2 = 4.5f;
	int n1 = int(f1);
	int n2 = int(f2);

	unsigned char c = -1; //c的值为255（该值对256取模后所得的余数）
	//signed char c = 256;  //c的值未定义）

	unsigned u1 = 42, u2 = 10;
	bool  b = (c != 255);
	std::cout << n1 << ";" << n2 << ";" << b << ";" << u2 - u1  << std::endl;
}

void testChar() {
	std::cout << "\tHi!\n";  // prints a tab followd by "Hi!" and a newline
	std::cout << "Hi \x4dO\115!\n"; // prints Hi MOM! followed by a newline
	std::cout << '\115' << '\n';    // prints M followed by a newline
}


#include <map>
#include <set>

#include <unordered_map>
#include <unordered_set>


using std::map;
using std::set;
using std::unordered_map;

// Foo must have ==
struct Foo { string s; };

// we'll see how to define our own operators in chapter 14
bool operator==(const Foo& l, const Foo& r) { return l.s == r.s; }

size_t FooHash(const Foo& f) { return hash<string>()(f.s); }

//using referenceCountSwap;
int main()
{
	//refrenceCountSwap::HasPtr::test();
	copyControl::test();
	//HasPtr::test();
	getchar();
	return 0;

	//smartPointer::test();
	// how to override just the hash function;
	 
	// use FooHash to generate the hash code; Foo must have an == operator
	unordered_set<Foo, decltype(FooHash)*> fooSet(10, FooHash);

	mapTest::test();
	//genericAlgorithm::test();
	
	//orderContainer::testSwap();
	//orderContainer::test();
	//ioTest::ioString1();
	//ioTest::ioString2();
	//ioTest::ioString3();
	//ioTest::ioString4();
	//ioTest::ioFile();
	//ioTest::testFile1();
	//ioTest::testFile2();


	try
	{
		throw MyExecption();
	}
	catch (MyExecption& e)
	{
		std::cout << "MyException caught" << std::endl;
		//std::cout << e.whate() << std::endl;
	} 


	//addItem::test();
	vectorTest::test();

	stringTest::getCin();
	stringTest::getLine();
	useShareVariable1::test();
	nShare = 2;
	useShareVariable2::test();
	testVariable();
	//testChar();
	addItem::test2();
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
