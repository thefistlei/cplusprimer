/*
 * 
*/
#ifndef FUNCTIONOBJECT_H
#define FUNCTIONOBJECT_H

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
namespace OverloadOperator2 
{  
    struct absInt {
        int operator()(int val) const {
            return val < 0 ? -val : val;
        }
    };

    class PrintString
    {
    public:
        PrintString(ostream& o = cout, char c = ' ') :
            os(o), sep(c) { }
        void operator()(const string& s) const
        {
            os << s << sep;
        }

    private:
        ostream& os;   // stream on which to write
        char sep;      // character to print after each output
    };

    int add(int i, int j) { return i + j; }

    string add(string i, string j) {
        return i + j;
    }

    void std_functionObject_test()
    {  
        // function-object class
        struct divide
        {
            int operator()(int denominator, int divisor)
            {
                return denominator / divisor;
            }
        };
         
         
        //lambda表达式，其产生一个未命名的函数对象类
        auto mod = [](int i, int j) { return i % j; }; 
        int (*fp) (int, int) = add; 

        function<int(int, int)> f1 = fp;  //函数指针
        function<int(int, int)> f2 = divide();  //函数对象类的指针
        function<int(int, int)> f3 = [](int i, int j) {return i * j; };  //lambda

        std::cout << f1(4, 2) << endl;   // prints 6
        cout << f2(4, 2) << endl;   // prints 2
        cout << f3(4, 2) << endl;   // prints 8 
        
        //使用map映射
        map<string, function<int(int, int)> > binops = {
            {"+",fp},  //函数指针
            {"-",std::minus<int>()},  //标准库函数对象
            {"/",divide()},  // 用户定义的函数对象
            {"*",[](int i,int j) {return i * j; }},  //未命名的lambda
            {"%",mod} //已命名的lambda对象
        };

        //这个时候insert是可以的 
        binops.insert({ "+", fp });	//函数指针
        binops.insert({ "/",divide() });	//函数对象
        binops.insert({ "%", mod });	//lambda表达式
        binops.insert({ "add" , [](int a, int b) {return add(a, b); } });//lambda表达式

        cout << binops["+"](10, 5)<<endl;//调用add(10, 5)
        cout << binops["-"](10, 5) << endl;
        cout << binops["/"](10, 5) << endl;	//使用divide对象调用括号运算符 
        cout << binops["*"](10, 5) << endl;
        cout << binops["%"](10, 5) << endl;//调用lambda函数对象
        cout << binops["add"](10, 5) << endl;//调用lambda函数对象    

        //调用代码
        //使用map映射
       // map<string, function<int(int, int)> > binops;
       // binops.insert({ "+", add });
        //error,不能将mode或divide insert到binope中，因为他们类型不是函数指针
       // binops.insert({ "%", mod });
    }

    void sysLib_functionObject_test2()
    {
        string a1 = "b1";
        string b1 = "a1";
        vector<string*> nameTable = {&a1 , &b1};    // vector of pointers
    // error: the pointers in nameTable are unrelated, so < is undefined
         sort(nameTable.begin(), nameTable.end(),             [](string* a, string* b) { return *a < *b; });
         for_each(nameTable.begin(), nameTable.end(), [](string* s)
             {std::cout << *s << endl; });

        // ok: library guarantees that less on pointer types is well defined
         vector<string*> nameTable2 = { &a1 , &b1 };    // vector of pointers 

         sort(nameTable2.begin(), nameTable2.end(), less<string*>());
         for_each(nameTable2.begin(), nameTable2.end(), [](string* s)
             {std::cout << *s << endl; });
    }

    void sysLib_functionObject_test()
    {
        vector<string> svec = { "a31", "b1" };
        sort(svec.begin(), svec.end(), greater<string>());
        for_each(svec.begin(), svec.end(), [](const string& s)
            {std::cout << s << endl; });

        plus<int> intAdd;	//可执行int加法的函数对
        negate<int> intNegate;	//可对int值取反的函数对象
        int sum = intAdd(10, 20);	//sum=30
        std::cout << sum << endl;
        sum = intAdd(10, intNegate(10));	//sum=0
        std::cout << sum << endl;
    }

    void lambda_functionObject_test2(vector<string>::size_type sz)
    { 
        std::vector<string> words = { "a31", "b1" };
        auto wc = find_if(words.begin(), words.end(), [sz](const string& a)
            {return a.size() >= sz; });
        std::cout << *wc << endl;

            //该 lambda 表达式产生的类将形如：
        class SizeComp
        {
        public:
            SizeComp(size_t n) :sz(n) { }
            bool operator()(const string& s)const { return s.size() >= sz; }
        private:
            size_t sz;
        };
        auto wc2 = find_if(words.begin(), words.end(), SizeComp(sz));
        std::cout << *wc2 << endl;
    }

    void lambda_functionObject_test()  
    {
        std::vector<string> words = { "a31", "b1" };
        stable_sort(words.begin(), words.end(), [](const string& a, const string& b)
            {return a.size() < b.size(); });

        for_each(words.begin(), words.end(), [](const string& s)
            {std::cout << s << endl; });

        //等价于下面的类：
        class ShorterString {
        public:
            bool operator()(const string& a, const string& b)
            {
                return a.size() < b.size();
            }
        };

        std::vector<string> words2 = { "a31", "b1" };
        stable_sort(words2.begin(), words2.end(), ShorterString());

        for_each(words2.begin(), words2.end(), [](const string& s)
            {std::cout << s << endl; });
    }


    void functionObject_test2() {
        string strText = "test";
        PrintString printer;  // uses the defaults; prints to cout
        printer(strText);     // prints s followed by a space on cout

        PrintString printer2(cerr, '_');
        printer2(strText);		//cerr中打印s，后面跟一个换行符


        //函数对象常常作为泛型算法的实参
        std::vector<string> vecStr = {"a1", "b1"};
        for_each(vecStr.begin(), vecStr.end(), PrintString(cerr, '-'));
    }


    void functionObject_test() {
        int i = -42;
        absInt absObj;
        int ui = absObj(i);	//i被传递给absObj.operator() 
        std::cout << ui << std::endl;
    }

    void test() {
        std_functionObject_test();
        //sysLib_functionObject_test2();
        //sysLib_functionObject_test();
        //lambda_functionObject_test2(3);
       // lambda_functionObject_test();
        //functionObject_test();
       // functionObject_test2();  
    } 
}

 
#endif
