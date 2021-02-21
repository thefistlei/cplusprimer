 

#ifndef COPYCONTROL_H 
#define COPYCONTROL_H
  

#include "StrVec.h"

#include "Folder.h"

#include <string>
using std::string;

 

#include <cstddef>
using std::size_t;

#include <iostream>
using std::cin; using std::cout; using std::endl;

 
#include <iostream> 
#include <fstream>
#include <sstream>
#include <istream>

using std::string;   
  


class copyControl {
public:
	copyControl(){}

	virtual ~copyControl() {}
private:
	void static print(const StrVec& svec)
	{
		for (auto it : svec)
			cout << it << " ";
		cout << endl;
	}

	StrVec static getVec(istream& is)
	{
		StrVec svec;
		string s;
		while (is >> s)
			svec.push_back(s);
		return svec;
	}
public:
	void static test()
	{
		//StrVec_test();
		//message_test();
		referenceQualifier_test();
	}

	void static referenceQualifier_test()
	{
		class Foo {
		public:
			Foo& operator=(const Foo&)& {
				return *this;
			}
			Foo& retFoo() {
				;	//返回一个引用，retFoo调用是一个左值 
				return *this;
			}

			Foo retVal() {
				;	//返回一个值，retVal调用是一个右值 
				return Foo();
			}

			//本对象是右值，因此可以原址排序
			Foo sorted()&&
			{
				sort(data.begin(), data.end());
				return *this;
			}

			//本对象是const或是一个左值，哪种情况我们都不能对其进行原址排序
			Foo sorted() const&
			{
				Foo ret(*this);			//拷贝一个副本
				sort(ret.data.begin(), ret.data.end());	//排序副本
				return ret;	//返回副本
			}
		private:
			vector<int> data;
		};

		//Foo& Foo::operator=(const Foo&)& 
		 

		Foo i, j;	//i,j是左值
		i = j;
		i.retFoo() = j;	//正确，retFoo()返回一个左值
		//i.retVal() = j;	//错误，retVal()返回一个右值
		i = j.retVal();	//正确
		j = j.retFoo(); //正确

		j.retVal().sorted();	//retVal()是一个右值，调用Foo::sorted() &&
		i.retFoo().sorted();	//retFoo()是一个左值，调用Foo::sorted() const & 
	}

	void static message_test()
	{
		string s1("contents1");
		string s2("contents2");
		string s3("contents3");
		string s4("contents4");
		string s5("contents5");
		string s6("contents6");

		// all new messages, no copies yet
		Message m1(s1);
		Message m2(s2);
		Message m3(s3);
		Message m4(s4);
		Message m5(s5);
		Message m6(s6);

		Folder f1;
		Folder f2;

		m1.save(f1); 
		m3.save(f1); 
		m5.save(f1);

		m1.save(f2);
		m2.save(f2); 
		m4.save(f2);
		m6.save(f2);

		m1.debug_print();
		f2.debug_print();

		// create some copies
		Message c1(m1);
		Message c2(m2), c4(m4), c6(m6);

		m1.debug_print();
		f2.debug_print();

		// now some assignments
		m2 = m3;
		m4 = m5;
		m6 = m3;
		m1 = m5;

		m1.debug_print();
		f2.debug_print();

		// finally, self-assignment
		m2 = m2;
		m1 = m1;

		m1.debug_print();
		f2.debug_print();

		vector<Message> vm;
		cout << "capacity: " << vm.capacity() << endl;
		vm.push_back(m1);

		cout << "capacity: " << vm.capacity() << endl;
		vm.push_back(m2);

		cout << "capacity: " << vm.capacity() << endl;
		vm.push_back(m3);

		cout << "capacity: " << vm.capacity() << endl;
		vm.push_back(m4);

		cout << "capacity: " << vm.capacity() << endl;
		vm.push_back(m5);

		cout << "capacity: " << vm.capacity() << endl;
		vm.push_back(m6);

		vector<Folder> vf;
		cout << "capacity: " << vf.capacity() << endl;
		vf.push_back(f1);

		cout << "capacity: " << vf.capacity() << endl;
		vf.push_back(f2);

		cout << "capacity: " << vf.capacity() << endl;
		vf.push_back(Folder(f1));

		cout << "capacity: " << vf.capacity() << endl;
		vf.push_back(Folder(f2));

		cout << "capacity: " << vf.capacity() << endl;
		vf.push_back(Folder());

		
		cout << "capacity: " << vf.capacity() << endl;

		Folder f3;
		f3.save(m6);
		vf.push_back(f3);
		cout << "capacity: " << vf.capacity() << endl;
		cout << endl;
	}

	void static StrVec_test()
	{
		string temp[] = { "one", "two", "three" };
		StrVec sv(begin(temp), end(temp));
 
		// run the string empty funciton on the first element in sv
		if (!sv[0].empty())
			sv[0] = "None"; // assign a new value to the first string 

		// we'll call getVec a couple of times
		// and will read the same file each time
	
		ifstream in("D:/code/cprimerGit/cplusprimer/cprimer/data/strvec-storyDataFile");
		//ifstream in("../data/strvec-storyDataFile");
		StrVec svec = getVec(in);
		print(svec);
		in.close();

		cout << "copy " << svec.size() << endl;
		auto svec2 = svec;
		print(svec2);

		cout << "assign" << endl;
		StrVec svec3;
		svec3 = svec2;
		print(svec3);

		StrVec v1, v2;
		v1 = v2;                   // v2 is an lvalue; copy assignment

		in.open("D:/code/cprimerGit/cplusprimer/cprimer/data/strvec-storyDataFile");
		v2 = getVec(in);          // getVec(in) is an rvalue; move assignment
		in.close();

		StrVec vec;  // empty StrVec
		string s = "some string or another";
		vec.push_back(s);      // calls push_back(const string&)
		vec.push_back("done"); // calls push_back(string&&)

		// emplace member covered in chpater 16
		s = "the end";
#ifdef VARIADICS
		vec.emplace_back(10, 'c'); // adds cccccccccc as a new last element
		vec.emplace_back(s);  // uses the string copy constructor
#else
		vec.push_back(string(10, 'c')); // calls push_back(string&&)
		vec.push_back(s);               // calls push_back(const string&)
#endif
		string s1 = "the beginning", s2 = s;
#ifdef VARIADICS
		vec.emplace_back(s1 + s2); // uses the move constructor
#else
		vec.push_back(string(s1 + s2)); // calls push_back(string&&)
#endif

	}  
}; 
#endif
