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
            cout << "operator int()" << endl;//����lambda��������   
            return val; 
        }
    private:
        std::size_t val;
    }; 

    void test1()
    {  
        SmallInt si;
        si = 4;	//���Ƚ�4��ʽת����SmallInt��Ȼ�����SmallInt::operator=  
        int n = si + 3;//���Ƚ�si��ʽ��ת����int��Ȼ��ִ�������ӷ� 
        cout << n << endl;//����lambda��������     
    }

    class SmallInt2 {
    public:
        //�����������Զ�ִ����һ����ת��

        //int operator int() const;//error��ָ���˷�������
        //operator int(int = 0) const;//error:ָ�����β�
        operator int() const { return 42; }//error��42����һ��ָ��
    };

    class SmallInt3 {
    public:
        //�����������Զ�ִ����һ����ת��
        explicit operator int() const { return val; }
    private:
        std::size_t val;
    };

    void test3()
    {
        //��ʽ����������ת��
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
        }	//��һ��Bת��ΪA
    };


    struct B {
        operator A() const {
            A a;
            return a;
        }	//Ҳ�ǰ�Bת��ΪA
    };

    A f(const A& a) {
        return a;
    }


    void test_ambiguous() {
      
        B b;
        // A a = f(b);	//�����Դ��󣬺����� f(B::operator A()) ����f(A::A(const B&)) ???

        A a1 = f(b.operator A());
        A a2 = f(A(b));
    }

    struct A2 {
        //��ò�Ҫ��������ת��Դ�����������͵�����ת��
        A2(int = 0) {};
        A2(double) {};
        //��ò�Ҫ��������ת���������������͵�����ת��
        operator int() const { return 1; }
        operator double() const { return 1.0f; }
    };

    void f2(long double) {

    }
     
    void test4() {
        A2 a;
       // f2(a); //�����Դ��󣬺����� f(A::operator int()),����f(A::operator double())

        long lg;
      //  A a2(lg);	//�����Դ��󣬺�����A::A(int) ���� A::A(double)

        int s = 42;
        A2 a3(s); //ʹ�� A::A(int)����Ϊshortת����int����shortת����double
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

        //manip(10);	//�����Դ��󣬺�����manip(C(10))����manip(D(10))
        manip(C(10));	//��ȷ����ʾ��ָ������
    }

    struct E
    {
        E(double) {}
    };

    void test6() {

        //manip(10);	//�����Դ��󣬺�����manip(C(10))����manip(D(10)) 
    }

    void test() {
        test1();
    } 
}

 
#endif
