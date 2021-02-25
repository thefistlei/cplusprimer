/*
 * 
*/
#ifndef OVERLOADOPERATOR_H
#define OVERLOADOPERATOR_H

//#include "Version_test.h"

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

 
#include <istream>
#include <ostream>


using std::cout;

#include <iostream>
using std::cin; using std::cout; using std::endl;


#include <iostream> 
#include <fstream>
#include <sstream> 

// forward declaration needed for friend declaration in StrBlobTest
namespace OverloadOperator 
{


    class StrBlobTest {

        friend std::istream& operator>>(std::istream&, StrBlobTest&);
        friend std::ostream& operator<<(std::ostream&, const StrBlobTest&);

        //friend class StrBlobTestPtr;
    public:
        typedef std::vector<std::string>::size_type size_type;
        int i;

        // constructors
       // StrBlobTest() : data(std::make_shared<std::vector<std::string>>()) { }
 
        StrBlobTest(std::string a, std::string b){
            data = new std::vector<std::string>();
            clear();
            push_back(a);
            push_back(b);
            i = 0;
        }

        StrBlobTest(std::istream& is) { is >> *this; }

        // size operations
        size_type size() const { return data->size(); }
        bool empty() const { return data->empty(); }
        void clear() const { return data->clear(); }




        bool contain(const std::string& t) {
            std::vector<std::string>::iterator it = (*data).begin();
            for (; it != (*data).end(); it++) {
                if (*it == t)
                    return true;
            }
            return false;
        }

        // add and remove elements
        void push_back(const std::string& t) { 
            data->push_back(t); 
        }
 
        // add and remove elements
        void erase(const std::string& t) {
            std::vector<std::string>::iterator it = data->begin();
            for (; it != data->end(); it++) {
                if (*it == t) {
                    data->erase(it);
                    break;
                }
            }
        } 
 
        std::string& operator[](std::size_t n)
        {
            return (*data)[n];
        }

        const std::string& operator[](std::size_t n) const
        {
            return (*data)[n];
        }
      
        StrBlobTest operator +(const StrBlobTest& rhs)
        {
            StrBlobTest sum = *this;

            for (int i = 0; i < rhs.size(); i++) {
                sum.push_back(rhs[i]);
            } 
            return sum;
        }

        StrBlobTest operator -(const StrBlobTest& rhs)
        {
            StrBlobTest sum = *this;

            for (int i = 0; i < rhs.size(); i++) {
                if(sum.contain(rhs[i]))
                    sum.erase(rhs[i]);
            }
            return sum;
        }

        bool operator ==(const StrBlobTest& rhs)
        {
            StrBlobTest sum = *this;

            if (sum.size() != rhs.size())
                return false;

            for (int i = 0; i < rhs.size(); i++) {
                if (sum[i] != rhs[i])
                    return false; 
            }

            return true;
        }

        bool operator !=(const StrBlobTest& rhs)
        {
            return !(*this == rhs);
        }

        //重载赋值运算符
        StrBlobTest& operator=(const StrBlobTest& rhs)
        {
            clear();

            for (int i = 0; i < rhs.size(); i++) {
                push_back(rhs[i]);
            }
            
            return *this;
        }

        //重载赋值运算符
        StrBlobTest& operator=(const char* psz)
        { 
            clear();  
            push_back(psz); 

            return *this;
        }

        //复合赋值运算符  
        StrBlobTest& operator+=(const StrBlobTest& rhs)
        { 
            for (int i = 0; i < rhs.size(); i++) {
                push_back(rhs[i]);
            }

            return *this;
        }

       
        bool operator < (const StrBlobTest& rhs)
        {
            StrBlobTest sum = *this;

            if (sum.size() != rhs.size())
                return sum.size() < rhs.size();

            for (int i = 0; i < rhs.size(); i++) {
                if (sum[i] != rhs[i])
                    return sum[i] < rhs[i];
            }
               
            return false;
        }

        //前置版本
        StrBlobTest& operator++()
        { 
            i++;

            if (i >= size())
                i = size() - 1;
            return *this;
        }

        StrBlobTest& operator--()
        { 
            i--;
             
            if (i < 0)
                i = 0;

            return *this;
        } 

        //后置版本
        StrBlobTest operator++(int)
        {
            StrBlobTest sum = *this;
            i++;

            if (i >= size())
                i = size() - 1;

            return sum;
        }

        StrBlobTest operator--(int)
        {
            StrBlobTest sum = *this;
            i--;

            if (i < 0)
                i = 0;

            return sum;
        } 

        std::string& operator*()const
        {  
            return (*data)[i];
        }

        std::string* operator->()const
        { 
            return &this->operator*();	//返回解引用结果的地址
        }

    private:
        //std::shared_ptr<std::vector<std::string>> data;
        std::vector<std::string> *data;

        // throws msg if data[i] isn't valid
        //void check(size_type i, const std::string& msg) const;
    };

    StrBlobTest operator +(const StrBlobTest& rhs, const StrBlobTest& lhs)
    {
        StrBlobTest sum = lhs;

        for (int i = 0; i < rhs.size(); i++) {
            sum.push_back(rhs[i]);
        }
        return sum;
    }
    
    StrBlobTest operator -(const StrBlobTest& rhs, const StrBlobTest& lhs)
    {
        StrBlobTest sum = lhs;

        for (int i = 0; i < rhs.size(); i++) {
            sum.erase(rhs[i]);
        }
        return sum;
    }
     

    ostream& operator<<(ostream& os, const StrBlobTest& item)
    {
        os << item.i << endl;

        for (int i = 0; i < item.size(); i++) {
            os << item[i] << endl;
        } 

        return os;
    }

    istream& operator >>(istream& is, StrBlobTest& item)
    {  
        is >> item.i; 

        std::string strInput;
        while(is >> strInput) 
        {
            item.push_back(strInput);
        } 
        return is;
    }


    void test() {
        StrBlobTest v1("a", "b");
        StrBlobTest v2("c", "d");

        StrBlobTest v3("e", "f");

        //std::cin >> v3;
        std::cout << v3 << std::endl;

        std::cout << (v1++).i << std::endl;
        std::cout << (++v1).i << std::endl;

        std::cout << (v1--).i << std::endl;
        std::cout << (--v1).i << std::endl;

        v3 = v1 + v2; 
        std::cout << v3 << std::endl;

        v1 += v2;
        std::cout << v1 << std::endl;
         
        v3 = v1 - v2;
        std::cout << v3 << std::endl;

        v3 = v1;
        std::cout << v3 << std::endl;

        bool bRet = v3 == v1;
        std::cout << bRet << std::endl;

        bRet = v3 != v1;
        std::cout << bRet << std::endl;
         
        v3 = "p";
        std::cout << v3 << std::endl;
         
        bRet = v1 < v2;
        std::cout << bRet << std::endl;

        *v1 = "123555";
        std::cout << (&v1)->size() << std::endl;//调用 std::string* operator->()const
        std::cout << v1->size() << std::endl;//调用 std::string* operator->()const
        std::cout << (*v1).size() << std::endl;
    } 
}

 
#endif
