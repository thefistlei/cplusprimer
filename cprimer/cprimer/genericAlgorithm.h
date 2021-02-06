 

#ifndef GENERICALGORITHM 
#define GENERICALGORITHM
  
#include <forward_list> 
#include <iostream> 
#include <fstream>
#include <sstream>
#include <istream>
#include <vector>
#include <list>
#include <numeric>
#include <array>
#include <algorithm>

#include<string>  
#include<deque>


#include<functional>
  
#include <iterator>

#include "TestSales_item.h"

using std::string;  
using std::vector;
using std::forward_list;
using std::list;

using std::cin; using std::cout; using std::endl;


using namespace std::placeholders;

class genericAlgorithm {
public:
	genericAlgorithm(){}

	virtual ~genericAlgorithm() {}
	 
	void static test_find()
	{
		int val = 42;

		vector<int> vec = {2, 42};
		auto result = find(vec.cbegin(), vec.cend(), val);
		cout << " " << *result;

		string strVal = "a value";
		list<string> lst = { "a value", "xxx", "yyy" };
		auto result3 = find(lst.cbegin(), lst.cend(), strVal);
		cout << " " << *result3;

		int ia[] = { 32, 3 }; 
		auto result2 = find(begin(ia), end(ia), val);
		cout << " " << *result2;
		
	} 

	void static test_accumulate()
	{ 
		vector<int> vec1 = { 1,2,3 };
		int result = accumulate(vec1.begin(), vec1.end(), 0);
		cout << " " << result;

		list<string> lst = { "a value", "xxx", "yyy" };
		string result2 = accumulate(lst.cbegin(), lst.cend(), string(""));
		cout << " " << result2;

		std::array<int, 10> ia = { 1,2,3,4,5,6,7,8,9,0 };
		auto result3 = accumulate(ia.cbegin(), ia.cend(), 0);//x,const char*û�мӷ�����
		cout << " " << result3;

	}

	void static test_findfirstof()
	{
		vector<int> vec = { 2, 42 };
		int ia[] = { 32, 3 };
		auto result = find_first_of(vec.cbegin(), vec.cend(), begin(ia), end(ia));
		if(result == vec.end())
			cout << "not found ";
		else
			cout << " " << *result; 
	}

	void static test_equal()
	{
		list<string> lst = { "a value", "xxx", "yyy" }; 
		vector<const char*> vec = { "a value", "xxx", "yyy" };  
		auto result = equal(vec.cbegin(), vec.cend(), lst.cbegin(), lst.cend());
		cout << " " << result;
	}

	void static test_count()
	{ 
		vector<int> v2 = { 4,5,6,7,8,9,4 }; 
		auto result = count(v2.cbegin(), v2.cend(), 4);
		cout << " " << result;
	}

	void static test_fill()
	{
		vector<int> v2 = { 4,5,6,7,8,9,4 };

		fill(v2.begin(), v2.end(), 0);//��ÿ��Ԫ�ض�����Ϊ0
		for(auto it:v2)
			cout << " " << it;
	}

	void static test_filln()
	{
		vector<int> v2 = { 4,5,6,7,8,9,4 };

		fill_n(v2.begin(), 3, 0);//��ÿ��Ԫ�ض�����Ϊ0
		for (auto it : v2)
			cout << " " << it;
	}

	void static test_back_inserter()
	{
		vector<int> v2 = { 4,5,6,7,8,9,4 };  
		fill_n(back_inserter(v2), 3, 0);//��ÿ��Ԫ�ض�����Ϊ0
		for (auto it : v2)
			cout << " " << it;
	}

	void static test_copy()
	{ 
		vector<int> v2 = { 4,5,6,7,8,9,4 };
		int a1[] = { 0,1,2,3,4,5,6 }; 
		auto ret = copy(begin(a1), end(a1), v2.begin());//��a1�����ݿ�����v2 
		for (auto it : v2)
			cout << " " << it;
	}

	void static test_replace()
	{
		vector<int> v2 = { 4,5,6,7,8,9,4 };
		int a1[] = { 0,1,2,3,4,5,6 };

		replace(v2.begin(), v2.end(), 4, 42); 
		for (auto it : v2)
			cout << " " << it;
	}

	void static test_replace_copy()
	{
		vector<int> v2 = { 4,5,6,7,8,9,4 };
		int a1[] = { 0,1,2,3,4,5,6 };

		vector<int> v3;
		replace_copy(v2.cbegin(), v2.cend(), back_inserter(v3), 4, 42);
		for (auto it : v3)
			cout << " " << it;
	}

	bool static less_len(const string& str1, const string& str2)
	{
		return str1.length() < str2.length();
	}

	void static test_sort()
	{ 
		vector<string> v2 = { "2222222222222","3" , "winter1", "apples1" , "apples" , "winter"};
	 
		vector<string> v1;  
		v1.assign(v2.begin(), v2.end());

		std::cout << "using stable_sort:";
		std::stable_sort(v1.begin(), v1.end(), less_len);
		for (auto it : v1)
			cout << " " << it;
		std::cout << '\n';

		v1.assign(v2.begin(), v2.end());

		std::cout << "using sort:";
		std::sort(v1.begin(), v1.end(), less_len);
		for (auto it : v1)
			cout << " " << it;
		std::cout << '\n';
	}

	void static test_unique()
	{
		vector<string> wordsNew;
		vector<string> words = { "the", "quick", "red", "fox","red", "the","slow" };
		sort(words.begin(), words.end());
		auto end_unique = unique(words.begin(), words.end()); 
		cout << " " << *end_unique;
		words.erase(end_unique, words.end());
		for (auto it : words)
			cout << " " << it;
		std::cout << '\n';
	}

	void static test_unique_copy()
	{
		vector<string> wordsNew = { "1", "2" };
		vector<string> words = { "the", "quick", "red", "fox","red", "the","slow" }; 

		//Create an insert_iterator for results
		insert_iterator<vector<string> > ins(wordsNew, wordsNew.end());

		auto end_unique = unique_copy(words.begin(), words.end(), ins);
		//cout << " " << end_unique;
		for (auto it : wordsNew)
			cout << " " << it;
		std::cout << '\n';
	}


	bool static isShorter(const string& s1, const string& s2)
	{
		return s1.size() < s2.size();
	}


  
	void static elimDups(vector<string>& words) {
		//���ֵ�˳������
		sort(words.begin(), words.end());
		auto end_unique = unique(words.begin(), words.end());
		words.erase(end_unique, words.end());
	}

	void static biggies(vector<string>& words, vector<string>::size_type sz) {	// ��words���ֵ�������ɾ���ظ�����
		elimDups(words);

		// ���������򣬳�����ͬ�ĵ���ά���ֵ���
		stable_sort(words.begin(), words.end(), isShorter);

		// ��ȡһ����������ָ���һ������size()>=sz��Ԫ��
		auto wc = find_if(words.begin(), words.end(), [sz](const string& a) { return a.size() >= sz; });
		// ��������size>=szԪ�ص���Ŀ
		auto count = words.end() - wc;
		cout << count << " " << ((count > 1) ? "word" : "words") << " of length " << sz << " or longer" << endl;

		//��ӡ���ȴ��ڵ��ڸ���ֵ�ĵ��ʣ�ÿ�����ʺ����һ���ո�
		for_each(wc, words.end(), [](const string& a) { cout << a << " "; });
		cout << endl;
	}

	void static test_predicate_2()
	{
		vector<string> words = { "the", "quick", "red", "fox","red", "the","slow", "seen" };	
		biggies(words, 4);	 
		cout << endl;
	}

	void static test_predicate()
	{ 
		//ʹ��ν�ʵ�����汾

		vector<string> words = { "the", "quick", "red", "fox","red", "the","slow" };
		cout << "Before: ";

		for (auto iter = words.begin(); iter != words.end(); ++iter) {
			cout << *iter << "  ";
		}
		cout << endl;
		sort(words.begin(), words.end(), isShorter); //ʹ��ν�ʽ�������
		cout << "After sort: ";

		for (const auto& s : words) {
			cout << s << "  ";
		}
		cout << endl; 
	} 

//#include <functional>  
	
	void static test_lamda1()
	{
		class testLamda {
		public:
			void static capture_value() {
				size_t v1 = 42;
				auto f = [v1] { return v1; };
				v1 = 0;
				auto j = f(); //j = 42
				cout << j << endl;
			}

			void static capture_refrence() {
				size_t v1 = 42;
				auto f = [&v1] { v1++; return v1; };
				v1 = 0;
				auto j = f(); //j = 0
				cout << j << " " << v1 <<endl;
			}

			void static capture_hide() {
				vector<string> words = { "the", "quick", "red", "fox","red", "the","slow" };
				biggies(words, words.size(), std::cout, '_');
			}

			void static capture_mixed() {
				vector<string> words = { "the", "quick", "red", "fox","red", "the","slow" };
				mixed_print(words, std::cout, '_');
			}

			void static mixed_print(vector<string> w, ostream& os = cout, char c = 'a', int n = 5) {
				// osʹ����ʽ���ò���ʽ; c��������ʽ��ֵ����ʽ
				for_each(w.begin(), w.end(), [&, c, n](const string& s) {
					os << s << c << n;
					});

				// cʹ����ʽֵ����ʽ; os��������ʽ�����ò���ʽ
				for_each(w.begin(), w.end(), [=, &os](const string& s) {
					os << s << c;
					}); 
			}					
	 
			ostream& print1(ostream& os, const string& s, char c)
			{
				return os << s << c;
			}

			void bindTest()
			{
				vector<string> word = { "the", "quick", "red", "fox","red", "the","slow" };
				//for_each(word.begin(), word.end(), bind(testprint, std::cout, std::placeholders::_1, ''));//error

				//for_each(word.begin(), word.end(), bind(testprint, ref(std::cout), " ", ' '));//error
			//	for_each(word.begin(), word.end(), bind2nd(print1, ref(os), _1, ' '));todo
			} 


			void static capture_mutabled() 
			{
				size_t v1 = 42;//�ֲ�����
				auto f = [v1]()mutable {return ++v1; };//f���Ըı���������ı�����ֵ
				v1 = 0;
				auto j = f();//jΪ43
				cout << j << endl;
			} 

			void static returnVal()
			{
				auto f = [](int i) {
					// ȡ����ֵ
					return i < 0 ? -i : i;
				};

				// �����޷��Զ��ƶ�
				auto f2 = [](int i) {
					// ȡ����ֵ
					if (i < 0)
						return -i;
					else
						return i; 
				};  
			}
			 
			void static test_captureHide()
			{ 
				vector<string> w = { "the", "quick", "red", "fox","red", "the","slow" };
				vector<string>::size_type sz;
				// sz������ʽֵ����ķ�ʽ
				auto wa = find_if(w.begin(), w.end(), [=](const string& s) {
					return s.size() >= sz;
				});
			}

			//ԭ��
			void static test_captureHide_biggies(std::vector<std::string>& words,
				std::vector<std::string>::size_type sz, ostream& os = cout, char c = ' ') {
				  
				// print result
				for_each(words.begin(), words.end(), [&, c](const std::string& s) {os << s << c; });
			}
			 


			//void static capture_mixed() {
			//	vector<string> words = { "the", "quick", "red", "fox","red", "the","slow" };
			//	mixed_print(words, std::cout, '_');
			//}

			//ԭ��
			void static biggies(std::vector<std::string>& words,
				std::vector<std::string>::size_type sz, ostream &os = cout, char c = ' ') {  


				stable_sort(words.begin(), words.end(),
					[](const string& s1, const string& s2) {  return s1.size() < s2.size(); });

				// print result
				for_each(words.begin(), words.end(), [&os, c](const std::string& s) {os << s << c; });
			}

			//ԭ��
			void static hide_biggies(std::vector<std::string>& words,
				std::vector<std::string>::size_type sz, std::ostream& os = cout, char c = ' ') {
				auto wc = std::find_if(words.begin(), words.end(), [sz](const std::string& a) { return a.size() > sz; });
			}
			
		};
		testLamda::capture_value();
		testLamda::capture_refrence();
		testLamda::capture_hide();
		testLamda::capture_mutabled();

		testLamda::returnVal(); 
	}

	void static test_iterator()
	{
		class testIterator {
		public:

			void static test_iterator1()
			{
				vector<int> foo = { 1,2,3 };
				auto it = inserter(foo, foo.end());
				*it = 4;

				//it = foo.insert(it, 4);
				//++it;

				for_each(foo.begin(), foo.end(), [](const int& a) {std::cout << a << ";"; });
				std::cout << "\n";


				deque<int> di, dbi, dfi;
				copy(foo.begin(), foo.end(), inserter(di, di.begin())); // ������������
				copy(foo.begin(), foo.end(), back_inserter(dbi));
				copy(foo.begin(), foo.end(), front_inserter(dfi));

				for_each(di.begin(), di.end(), [](const int& a) {std::cout << a << ";"; });
				std::cout << "\n";
				for_each(dbi.begin(), dbi.end(), [](const int& a) {std::cout << a << ";"; });

				std::cout << "\n";
				for_each(dfi.begin(), dfi.end(), [](const int& a) {std::cout << a << ";"; });
			}

			void static iostream_istream() {
				/*
				* ����������������
				* ֻ�м���ctrl+d��������󣬺����䷽��ִ�С�
				*/
				istream_iterator<int> in_iter(std::cin);


				istream_iterator<int> eof;
				vector<int> vec;

				// ��������������Ϊ������vector������ֵ
				vector<int> vec2(in_iter, eof);

				while (in_iter != eof)
					vec.push_back(*in_iter++);

				vector<int>::const_iterator it = vec.begin();
				for (; it != vec.end(); ++it)
					cout << *it << endl;
			}

			void static iostream_ostream() {
				ostream_iterator<string> out_iter(cout, "/n");
				istream_iterator<string> in_iter(cin), eof;
				while (in_iter != eof)
					*out_iter++ = *in_iter++;
			}

			void static iostream_ostream2() {
				std::ostream_iterator<int> iter_out(std::cout, " ");    // ÿ��������������һ���ո�
				std::vector<int> vec = { 1, 3, 5 };
				for (auto i : vec)
					*iter_out++ = i;    // i��д�뵽cout��

				for (auto i : vec)
					iter_out = i;    // ����������ȼۣ���Ϊ*��++ʵ���ϲ���iter_out���κ�����

				std::cout << std::endl;
			}

			void static iostream_ostream3() {
				std::ostream_iterator<int> iter_out(std::cout, " ");    // ÿ��������������һ���ո�
				std::vector<int> vec = { 1, 3, 5 };
				copy(vec.begin(), vec.end(), iter_out);
				cout << endl;
			}

			void static iostream_TestSales_item() {
				istream_iterator<TestSales_item> in_iter(cin), eof;
			 
				ostream_iterator<TestSales_item> out_iter(cout, "\n");
				//����Sales_item����sum��������in_iter�ڵ�Ԫ�س�ʼ��������in_iter��ȡ��һ��ֵ
				TestSales_item sum = *in_iter++;
				//����whileѭ������in_iter��������û���������󣬲���û�е����ļ�ĩβ��ʱ��ѭ������
				while (in_iter != eof)
				{
					//����ղŶ�ȡ��Ԫ�ص�isbn��sum�е�Sales_data��isbn��ȣ���ô�����Ԫ�ؼӵ�sum�У���
					//in_iter��ȡ��һ��ֵ
					if (in_iter->isbn == sum.isbn)
					{
						sum += *in_iter++;
					}
					//����¶�ȡ�Ķ����isbn������sum��Ԫ�ص�isbn���������sum�еĶ���Ȼ�����*in_iter
					//��ֵ��sum��Ȼ��in_iter�ٶ�ȡ��һ��ֵ
					else
					{
						*out_iter++ = sum;
						sum = *in_iter++;
					}
				}
			}
			
			void static resverseIterator() {
				string line = "lei,ye,wang";

				auto comma = find(line.cbegin(), line.cend(), ',');
				cout << string(line.cbegin(), comma) << endl;

				auto rcomma = find(line.crbegin(), line.crend(), ',');
				cout << string(line.crbegin(), rcomma) << endl;

				cout << string(rcomma.base(), line.cend()) << endl; 
				cout << endl;
			}

			/*
			class Sales_item
			{
			public:
				Sales_item(const std::string& book) :isbn(book), units_sold(0), revenue(0.0) {}
				Sales_item(std::istream& is) { is >> *this; }

				friend std::istream& operator>>(std::istream&, Sales_item&);
				friend std::ostream& operator<<(std::ostream&, Sales_item&);

				Sales_item() :units_sold(0), revenue(0.0) {}
			public:
				std::string isbn;
				unsigned units_sold;
				double revenue;

				inline istream& operator>>(istream& in, Sales_item& s)
				{
					double price;
					in >> this->isbn >> this->units_sold >> price;
					if (in)
						this->revenue = this->units_sold * price;
					//else
						//this = Sales_item();
					return in;
				}

				inline ostream& operator<<(ostream& out)const
				{
					out << this->isbn << "\t" << this->units_sold << "\t" << this->revenue << "\t";
					return out;
				}

				inline ostream& operator<<(ostream& out)
				{
					out << this->isbn << "\t" << this->units_sold << "\t" << this->revenue << "\t";
					return out;
				}

				inline void operator=(const Sales_item& lhs)
				{
					this->revenue == lhs.revenue;
				}

			};
			*/ 

			

		};

		//testIterator::test_iterator1();
		//testIterator::iostream_istream();
		//testIterator::iostream_ostream(); 
		//testIterator::iostream_ostream3();
		//testIterator::iostream_TestSales_item(); 
		testIterator::resverseIterator();
		
	}

	void static test_bind()
	{
		class testBind {
		public: 
			std::ostream& print(std::ostream& os, const string& s, char c)
			{
				return os << s << c;
			}
 
			void static test() {
				vector<string> word = { "the", "quick", "red", "fox","red", "the","slow" };
				//for_each(word.begin(), word.end(), std::bind(print, os, _1, ''));//error
			}
		};

		testBind::test();
	} 


	void static test()
	{
		test_iterator();

		//test_lamda1();
		//test_bind();
		//test_predicate_2();
		//test_predicate();
		//test_unique_copy();
		//test_unique();
		//test_sort();
		//test_replace_copy();
		//test_replace();
		//test_copy();
		//test_back_inserter();
		//test_filln(); 
		//test_fill();
		//test_count(); 
		//test_equal(); 
		//test_findfirstof(); 
		//test_accumulate(); 
		//test_find();
	}



	////swap��
	//v1 = { 4,5,6,7,8,9 };
	//v2 = { 1,2,3 };
}; 
#endif
