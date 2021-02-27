/*
 * 
*/
#ifndef CLASSTYPEEXCHANGE_H
#define CLASSTYPEEXCHANGE_H

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
namespace classTypeExchange
{  
    class SmallInt {
    public:
        SmallInt(int i = 0) :val(i)
        {
            if (i < 0 || i > 255)
                throw std::out_of_range("Bad SmallInt value");
        }
        operator int() const {
            cout << "operator int()" << endl;//调用lambda函数对象   
            return val; 
        }
    private:
        std::size_t val;
    }; 

    void test1()
    {  
        SmallInt si;
        si = 4;	//首先将4隐式转换成SmallInt，然后调用SmallInt::operator=  
        int n = si + 3;//首先将si隐式地转换成int，然后执行整数加法 
        cout << n << endl;//调用lambda函数对象     
    }

    class SmallInt2 {
    public:
        //编译器不会自动执行这一类型转换

        //int operator int() const;//error：指定了返回类型
        //operator int(int = 0) const;//error:指定了形参
        operator int() const { return 42; }//error：42不是一个指针
    };

    class SmallInt3 {
    public:
        //编译器不会自动执行这一类型转换
        explicit operator int() const { return val; }
    private:
        std::size_t val;
    };

    void test3()
    {
        //显式地请求类型转换
        //SmallInt3 si = 3;
        //int n = si + 3;//error
        SmallInt3 si;
        static_cast<int>(si) + 3;// 
    }
          

    struct B;
    struct A
    {
        A() = default;
        A(const B&) {
        }	//把一个B转换为A
    };


    struct B {
        operator A() const {
            A a;
            return a;
        }	//也是把B转换为A
    };

    A f(const A& a) {
        return a;
    }


    void test_ambiguous() {
      
        B b;
        // A a = f(b);	//二义性错误，含义是 f(B::operator A()) 还是f(A::A(const B&)) ???

        A a1 = f(b.operator A());
        A a2 = f(A(b));
    }

    struct A2 {
        //最好不要创建两个转换源都是算术类型的类型转换
        A2(int = 0) {};
        A2(double) {};
        //最好不要创建两个转换对象都是算术类型的类型转换
        operator int() const { return 1; }
        operator double() const { return 1.0f; }
    };

    void f2(long double) {

    }
     
    void test4() {
        A2 a;
       // f2(a); //二义性错误，含义是 f(A::operator int()),还是f(A::operator double())

        long lg;
      //  A a2(lg);	//二义性错误，含义是A::A(int) 还是 A::A(double)

        int s = 42;
        A2 a3(s); //使用 A::A(int)，因为short转换成int由于short转换成double
    }

    struct C
    {
        C(int) {};
    };
    struct D
    {
        D(int) {};
    };

    void manip(const C&) {

    }
    void manip(const D&) {

    }

    void test5() {

        //manip(10);	//二义性错误，含义是manip(C(10))还是manip(D(10))
        manip(C(10));	//正确，显示的指明调用
    }

    struct E
    {
        E(double) {}
    };

    void test6() {

        //manip(10);	//二义性错误，含义是manip(C(10))还是manip(D(10)) 
    }

    void test() {
        test1();
    } 
}

 
#endif
