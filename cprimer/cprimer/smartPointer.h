 

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
        shared_ptr<string> p1; //shared_ptr,����ָ��string 
        shared_ptr<list<int>> p2; //shared_ptr,����ָ��int��list

        //ʹ��make_shared����
        shared_ptr<int> p3 = make_shared<int>(42);
        shared_ptr<string> p4 = make_shared<string>(10, '9');
        shared_ptr<int> p5 = make_shared<int>();
        auto p6 = make_shared<vector<string>>();

        shared_ptr<string>sp;
        make_shared<string>();         //��̬�����ڴ�Ĭ�ϳ�ʼ��������Ҫ������, Ĭ�ϳ�ʼ���õ����ǿ�ָ��
        make_shared<string>("a");      //��̬�����ڴ�ֵ��ʼ��
        shared_ptr<string>sp2 = make_shared<string>();   //��ʼ������ָ��
        shared_ptr<string>sp3 = make_shared<string>("b");//��ʼ������ָ��

       //��new���
        //shared_ptr<int> p1 = new int(1024); //error
        shared_ptr<int> p2New(new int(1024)); //ok, ֱ�ӳ�ʼ����ʽ��
    }

	void static get_test()
	{ 
        shared_ptr<int>p(new int(42));
        int* q = p.get();
        cout << "count:" << p.use_count() << *q << endl;
       // delete q; //error:
        {
            auto t = shared_ptr<int>(q); //ת��   
            cout << "count:" << t.use_count() << endl;
        }
        int nVal = *p;
        cout << nVal << endl;
	}   

    shared_ptr<string> static fun1(shared_ptr<string> sp5)//���ݲ����ṹ��һ�����������������������н������ͷ�
    {
        auto sp6 = sp5;                            //������ʱ����ֵ��������������
        cout << "sp5 use_count:" << sp5.use_count() << endl;
        cout << "sp5 is_unique:" << sp5.unique() << endl;
        return sp6;
    }

    void static copy_test()
    { 
        shared_ptr<string>sp = make_shared<string>("aa");
        auto sp3 = make_shared<string>(10, 'a');//ͨ��ʹ��auto���򻯶���һ������������make_shared�Ľ�������ַ�ʽ�Ƚϼ򵥡�
        cout << "sp use_count:" << sp.use_count() << endl;
        auto sp2(sp);                          //����sp,count����������
        cout << "sp use_count:" << sp.use_count() << endl;
        cout << "sp is_unique:" << sp.unique() << endl;
        sp2 = sp3;                             //��ֵsp2,���������
        cout << "sp use_count:" << sp.use_count() << endl;
        cout << "sp is_unique:" << sp.unique() << endl;
        auto sp4(sp3);
        cout << "sp3 use_count:" << sp3.use_count() << endl;
        cout << "sp3 is_unique:" << sp3.unique() << endl;
        sp = sp3;//spָ��sp3ָ���,spָ��ı����١�
        cout << "sp use_count:" << sp.use_count() << endl;
        cout << "sp is_unique:" << sp.unique() << endl;
        auto sp7 = fun1(sp);
        cout << "sp7 use_count:" << sp.use_count() << endl;
        cout << "sp7 is_unique:" << sp.unique() << endl; 
    }

    void static disconnect_test()
    {
        struct destination {
        };                //��������ʲô
        struct connection {
        };

        class test2 {
        public:
            connection& connect(connection* s)
            {
                cout << "��������..." << endl;
                s = new connection();
                return *s;
            }

            void static disconnect(connection* s)
            {
                cout << "���ڶϿ�����..." << endl;
            }

            void test()
            {
                connection p;
                connection* d = new connection();
                p = connect(d);
                //shared_ptr<connection>sp(&p,disconnect);   
                //error:lambda������ɾ����������ô�����б�ҲҪ��ɾ������һ�£���Ϊdelete�ڲ���free(p)��
                //shared_ptr<connection>sp(&p, [&p] { disconnect(&p); });
                shared_ptr<connection>sp(&p, [](connection* s) { disconnect(s); });
            } 
        };
                 //ʹ�������������Ϣ

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
                disconnect(c);//���û�е���disconnect����ô��Զ����Ͽ����ӡ�
            }

          
            void end_disconnect(connection* p) { 
                disconnect(p);
            }

            void f2(destination* d)
            {
                connection* c = connect(d);

                shared_ptr<connection*>p(c, end_disconnect);

//                shared_ptr<connection*>p(c, end_disconnect);
                //f�˳�ʱ�����Զ�����end_connect��
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
                disconnect(c);//���û�е���disconnect����ô��Զ����Ͽ����ӡ�
            }
            //ʹ������ָ���Ż��������Լ�������delete���汾���delete
 
            void static end_disconnect(connection* p) { 
                disconnect(*p);
            }

            void f2(destination& d)
            {
                connection c = connect(&d); 

                //shared_ptr<connection*>p = make_shared<connection*>(&c); 
                
                shared_ptr<connection>p2(&c, [](connection* s) { end_disconnect(s); });
                //f�˳�ʱ�����Զ�����end_connect��
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
        };                //��������ʲô
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

                //����Ŀ����͸�ֵ
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
                cout << "��������..." << endl;
                d = new connection();
                return d;
            }

            void static disconnect(connection* p)
            {
                cout << "�Ͽ�����..." << endl;
            }

            void test_disconnect()
            {
                connection* p = new connection(); 
                connection* p2 = connect(p);
                cout << p << endl;
                cout << p2 << endl;
                unique_ptr<connection, decltype(disconnect)*>q(p2, disconnect);
                //�ڼ��������ṩ���ͣ�Բ�������ṩ�������е����͵Ķ���
                //ʹ��decltype()�ؼ��ַ���һ���������ͣ����Ա������һ��*����ָ������ʹ�õ���һ��ָ��

                //p.release();                   //error:p2�����ͷ��ڴ棬���Ҷ�ʧ��ָ��
                //auto q2 = p.release();   //q ��int * ���ͣ� �ǵ�delete�ͷ�q
            }

           
        };

        uniqueSharedTest obj;
        obj.define();
        obj.test_disconnect();   
    }

    void static test_array()
    {
        // up ָ��һ������10���ǳ�ʼ��int������
        unique_ptr<int[]> up(new int[10]); 
        for (size_t i = 0; i != 10; ++i)
            up[i] = i;  
        up.release(); // �Զ�����delete[]������ָ��

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

                weak_ptr<int> wp(p);//wp ������p;p�����ü���δ�ı䣬���ʹ��ʱ����ʹ�ú���lock()

                p.reset();//�ͷ�p
                if (shared_ptr<int> np = wp.lock()) {//���np��������������

                    //��if�У�np��p�������
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
