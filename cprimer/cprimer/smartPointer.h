 

#ifndef SMARTPOINTER_H 
#define SMARTPOINTER_H


//#include "wordTransform.h"

#include "StrBlob.h"

#include <memory>

#include <iostream>
using std::cin; using std::cout; using std::endl;

#include <forward_list> 
#include <iostream> 
#include <fstream>
#include <sstream>
#include <istream>

  
 

#include <string>
using std::string;
 
using std::ifstream;
 
using std::cin; using std::cout; using std::cerr;
using std::endl;

#include <cstdlib>  // for EXIT_FAILURE

#include "TextQuery.h" 


class smartPointer {
public:
	smartPointer(){} 
	virtual ~smartPointer() {}
	 
    void static constructor_test()
    {
        shared_ptr<string> p1; //shared_ptr,可以指向string 
        shared_ptr<list<int>> p2; //shared_ptr,可以指向int的list

        //使用make_shared函数
        shared_ptr<int> p3 = make_shared<int>(42);
        shared_ptr<string> p4 = make_shared<string>(10, '9');
        shared_ptr<int> p5 = make_shared<int>();
        auto p6 = make_shared<vector<string>>();

        shared_ptr<string>sp;
        make_shared<string>();         //动态分配内存默认初始化，必须要有括号, 默认初始化得到的是空指针
        make_shared<string>("a");      //动态分配内存值初始化
        shared_ptr<string>sp2 = make_shared<string>();   //初始化智能指针
        shared_ptr<string>sp3 = make_shared<string>("b");//初始化智能指针

       //和new结合
        //shared_ptr<int> p1 = new int(1024); //error
        shared_ptr<int> p2New(new int(1024)); //ok, 直接初始化形式。
    }

	void static get_test()
	{ 
        shared_ptr<int>p(new int(42));
        int* q = p.get();
        cout << "count:" << p.use_count() << *q << endl;
       // delete q; //error:
        {
            auto t = shared_ptr<int>(q); //转换   
            cout << "count:" << t.use_count() << endl;
        }
        int nVal = *p;
        cout << nVal << endl;
	}   

    shared_ptr<string> static fun1(shared_ptr<string> sp5)//传递参数会构造一个，计数器递增，函数运行结束后释放
    {
        auto sp6 = sp5;                            //创建临时并赋值，计数器递增。
        cout << "sp5 use_count:" << sp5.use_count() << endl;
        cout << "sp5 is_unique:" << sp5.unique() << endl;
        return sp6;
    }

    void static copy_test()
    { 
        shared_ptr<string>sp = make_shared<string>("aa");
        auto sp3 = make_shared<string>(10, 'a');//通常使用auto来简化定义一个对象来保存make_shared的结果，这种方式比较简单。
        cout << "sp use_count:" << sp.use_count() << endl;
        auto sp2(sp);                          //拷贝sp,count计数会增加
        cout << "sp use_count:" << sp.use_count() << endl;
        cout << "sp is_unique:" << sp.unique() << endl;
        sp2 = sp3;                             //赋值sp2,计数会减少
        cout << "sp use_count:" << sp.use_count() << endl;
        cout << "sp is_unique:" << sp.unique() << endl;
        auto sp4(sp3);
        cout << "sp3 use_count:" << sp3.use_count() << endl;
        cout << "sp3 is_unique:" << sp3.unique() << endl;
        sp = sp3;//sp指向sp3指向的,sp指向的被销毁。
        cout << "sp use_count:" << sp.use_count() << endl;
        cout << "sp is_unique:" << sp.unique() << endl;
        auto sp7 = fun1(sp);
        cout << "sp7 use_count:" << sp.use_count() << endl;
        cout << "sp7 is_unique:" << sp.unique() << endl; 
    }

    void static disconnect_test()
    {
        struct destination {
        };                //正在连接什么
        struct connection {
        };

        class test2 {
        public:
            connection& connect(connection* s)
            {
                cout << "正在连接..." << endl;
                s = new connection();
                return *s;
            }

            void static disconnect(connection* s)
            {
                cout << "正在断开连接..." << endl;
            }

            void test()
            {
                connection p;
                connection* d = new connection();
                p = connect(d);
                //shared_ptr<connection>sp(&p,disconnect);   
                //error:lambda代表了删除函数。那么参数列表也要和删除函数一致，因为delete内部是free(p)。
                //shared_ptr<connection>sp(&p, [&p] { disconnect(&p); });
                shared_ptr<connection>sp(&p, [](connection* s) { disconnect(s); });
            } 
        };
                 //使用连接所需的信息

        class test {
        public:
            test() {}
            ~test() {}
             
            /*
            connection* connect(destination*) {
                connection* ret = new connection();
                return ret;
            }

            void disconnect(connection*) {
                cout << "disconnect connection" << endl;
            }

            void f(destination* d)
            {
                connection* c = connect(d);
                disconnect(c);//如果没有调用disconnect，那么永远不会断开连接。
            }

          
            void end_disconnect(connection* p) { 
                disconnect(p);
            }

            void f2(destination* d)
            {
                connection* c = connect(d);

                shared_ptr<connection*>p(c, end_disconnect);

//                shared_ptr<connection*>p(c, end_disconnect);
                //f退出时，会自动调用end_connect。
            }
            */

            connection connect(destination*) {
                connection obj;
                return obj;
            }

            void static disconnect(connection) {
                cout << "disconnect connection" << endl; 
            }

            void f(destination& d)
            {
                connection c = connect(&d);
                disconnect(c);//如果没有调用disconnect，那么永远不会断开连接。
            }
            //使用智能指针优化，等于自己定义了delete代替本身的delete
 
            void static end_disconnect(connection* p) { 
                disconnect(*p);
            }

            void f2(destination& d)
            {
                connection c = connect(&d); 

                //shared_ptr<connection*>p = make_shared<connection*>(&c); 
                
                shared_ptr<connection>p2(&c, [](connection* s) { end_disconnect(s); });
                //f退出时，会自动调用end_connect。
            }


        };

        test2 obj;
        obj.test();

        test obj1;

        destination* d = new destination();
        obj1.f2(*d);
    }

    void static uniqueShared_test()
    { 
        struct destination {
        };                //正在连接什么
        struct connection {
        };

        class uniqueSharedTest {
        public:
            uniqueSharedTest() {};
            ~uniqueSharedTest() {};

            void static define()
            {
                unique_ptr<string> p1(new string());
                 
                // transfers ownership from p1 (which points to the string Stegosaurus) to p2
                unique_ptr<string> p2(p1.release()); // release makes p1 null

                unique_ptr<string> p3(new string("Trex"));

                // transfers ownership from p3 to p2
                p2.reset(p3.release()); // reset deletes the memory to which p2 had pointed 

                //特殊的拷贝和赋值
                int i = 10;
                unique_ptr<int> testInt = clone(i);
            }

            unique_ptr<int> static clone(int p)
            {
                unique_ptr<int>q(new int(p));
                return q;
                //return unique<int>q(new int(p));
            }   

            connection* connect(connection* d)
            {
                cout << "正在连接..." << endl;
                d = new connection();
                return d;
            }

            void static disconnect(connection* p)
            {
                cout << "断开连接..." << endl;
            }

            void test_disconnect()
            {
                connection* p = new connection(); 
                connection* p2 = connect(p);
                cout << p << endl;
                cout << p2 << endl;
                unique_ptr<connection, decltype(disconnect)*>q(p2, disconnect);
                //在尖括号中提供类型，圆括号内提供尖括号中的类型的对象。
                //使用decltype()关键字返回一个函数类型，所以必须添加一个*号来指出我们使用的是一个指针

                //p.release();                   //error:p2不会释放内存，而且丢失了指针
                //auto q2 = p.release();   //q 是int * 类型， 记得delete释放q
            }

           
        };

        uniqueSharedTest obj;
        obj.define();
        obj.test_disconnect();   
    }

    void static test_array()
    {
        // up 指向一个包含10个非初始化int的数组
        unique_ptr<int[]> up(new int[10]); 
        for (size_t i = 0; i != 10; ++i)
            up[i] = i;  
        up.release(); // 自动调用delete[]销毁其指针

        // to use a shared_ptr we must supply a deleter
        shared_ptr<int> sp(new int[10], [](int* p) { delete[] p; });
        // shared_ptrs don't have subscript operator 
        // and don't support pointer arithmetic
        for (size_t i = 0; i != 10; ++i)
            *(sp.get() + i) = i;  // use get to get a built-in pointer
        sp.reset(); // uses the lambda we supplied  
    }

    void static weakShared_test()
    {  
        class weakSharedTest {
        public:
            weakSharedTest() {};
            ~weakSharedTest() {};

            void static define()
            {
                auto p = make_shared<int>(42);

                weak_ptr<int> wp(p);//wp 弱共享p;p的引用计数未改变，因此使用时必须使用函数lock()

                p.reset();//释放p
                if (shared_ptr<int> np = wp.lock()) {//如果np不空则条件成立

                    //在if中，np与p共享对象
                    cout << "lock not null"<<endl;
                }
            }
        };

        weakSharedTest obj;
        obj.define();
    }

    void static allocClass_define() 
    {
        const size_t n = 100;
        allocator<string> allocStr;      // object that can allocate strings
        auto p = allocStr.allocate(n);   // allocate n unconstructed strings

        //cout << *p << endl;

        auto q = p; // q will point to one past the last constructed element
        allocStr.construct(q++);         // *q is the empty string
        cout << *(q - 1) << endl;

        allocStr.construct(q++, 10, 'c'); // *q is cccccccccc
        cout << *(q - 1) << endl;

        //allocStr.construct(q++, "hi");    // *q is hi!
        //cout << *(q - 1) << endl;

        int nCount = 0;
        cout << *p << endl;  // ok: uses the string output operator
        while (q != p) {
            nCount++;
            allocStr.destroy(--q);  // free the strings we actually allocated
        }
        cout << nCount << endl;  // ok: uses the string output operator

        allocStr.deallocate(p, n);  // return the memory we allocated

        p = allocStr.allocate(n);   // allocate n unconstructed strings
        string s;
        q = p;                   // q points to the memory for first string
        ifstream in("E:/temp/storyDataFile");
        while (in >> s && q != p + n)
            allocStr.construct(q++, s); // construct only as many strings as we need
        size_t size = q - p;         // remember how many strings we read

        // use the array

        cout << "read " << size << " strings" << endl;

        for (q = p + size - 1; q != p; --q)
            allocStr.destroy(q);         // free the strings we allocated
        allocStr.deallocate(p, n);       // return the memory we allocated

        in.close();
        in.open("E:/temp/storyDataFile");
        p = new string[n];            // construct n empty strings
        q = p;                        // q points to the first string
        while (in >> s && q != p + n)
            *q++ = s;                 // assign a new value to *q
        size = q - p;                 // remember how many strings we read

        cout << "read " << size << " strings" << endl;
    }

    void static allocClass_alloc()
    {
        vector<int> vi{ 1,2,3,4,5,6,7,8,9 };
  
        allocator<int> alloc;

        // allocate twice as many elements as vi holds
        auto p = alloc.allocate(vi.size() * 2);

        // construct elements starting at p as copies of elements in vi
        auto q = uninitialized_copy(vi.begin(), vi.end(), p);
 

        // initialize the remaining elements to 42
        uninitialized_fill_n(q, vi.size(), 42);

        for (size_t i = 0; i != vi.size(); ++i)
        cout << *(p + i) << " ";
        cout << endl;

        for (size_t i = 0; i != vi.size(); ++i)
        cout << *(q + i) << " ";
        cout << endl;

        alloc.deallocate(p, vi.size());
    }

    void static strBob_test1()
    {
        StrBlob b1;
        { 
            string temp[] = { "a", "an", "the" };
            StrBlob b2(begin(temp), end(temp));
 
            b1 = b2;
            b2.push_back("about");
            cout << b2.size() << endl;
        }

        cout << b1.size() << endl;

        for (auto it = b1.begin(); neq(it, b1.end()); it.incr())
            cout << it.deref() << endl;

    }

    void static textQuery_test1()
    {
        // open the file from which user will query words
        ifstream infile;
        infile.open("E:/temp/queryText");

        // infile is an ifstream that is the file we want to query
        TextQuery tq(infile);  // store the file and build the query map

        // iterate with the user: prompt for a word to find and print results
        while (true) {
            cout << "enter word to look for, or q to quit: ";

            // stop if we hit end-of-file on the input or if a 'q' is entered
            string s;
            if (!(cin >> s) || s == "q") 
                break;

            // run the query and print the results
            print(cout, tq.query(s)) << endl;
        } 
    }

    void static test()
    {
        //get_test();
        //copy_test();
        //disconnect_test();
        //uniqueShared_test();
       //test_array();
       //weakShared_test();
        //allocClass_define();
        //allocClass_alloc();
        //strBob_test1();
        textQuery_test1();
    }
}; 
#endif
