 

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
		auto result3 = accumulate(ia.cbegin(), ia.cend(), 0);//x,const char*没有加法运算
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

		fill(v2.begin(), v2.end(), 0);//将每个元素都重置为0
		for(auto it:v2)
			cout << " " << it;
	}

	void static test_filln()
	{
		vector<int> v2 = { 4,5,6,7,8,9,4 };

		fill_n(v2.begin(), 3, 0);//将每个元素都重置为0
		for (auto it : v2)
			cout << " " << it;
	}

	void static test_back_inserter()
	{
		vector<int> v2 = { 4,5,6,7,8,9,4 };  
		fill_n(back_inserter(v2), 3, 0);//将每个元素都重置为0
		for (auto it : v2)
			cout << " " << it;
	}

	void static test_copy()
	{ 
		vector<int> v2 = { 4,5,6,7,8,9,4 };
		int a1[] = { 0,1,2,3,4,5,6 }; 
		auto ret = copy(begin(a1), end(a1), v2.begin());//把a1的内容拷贝给v2 
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
		//按字典顺序排序
		sort(words.begin(), words.end());
		auto end_unique = unique(words.begin(), words.end());
		words.erase(end_unique, words.end());
	}

	void static biggies(vector<string>& words, vector<string>::size_type sz) {	// 将words按字典序排序，删除重复单词
		elimDups(words);

		// 按长度排序，长度相同的单词维持字典序
		stable_sort(words.begin(), words.end(), isShorter);

		// 获取一个迭代器，指向第一个满足size()>=sz的元素
		auto wc = find_if(words.begin(), words.end(), [sz](const string& a) { return a.size() >= sz; });
		// 计算满足size>=sz元素的数目
		auto count = words.end() - wc;
		cout << count << " " << ((count > 1) ? "word" : "words") << " of length " << sz << " or longer" << endl;

		//打印长度大于等于给定值的单词，每个单词后面接一个空格
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
		//使用谓词的排序版本

		vector<string> words = { "the", "quick", "red", "fox","red", "the","slow" };
		cout << "Before: ";

		for (auto iter = words.begin(); iter != words.end(); ++iter) {
			cout << *iter << "  ";
		}
		cout << endl;
		sort(words.begin(), words.end(), isShorter); //使用谓词进行排序
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
				// os使用隐式引用捕获方式; c必须是显式的值捕获方式
				for_each(w.begin(), w.end(), [&, c, n](const string& s) {
					os << s << c << n;
					});

				// c使用隐式值捕获方式; os必须是显式的引用捕获方式
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
				size_t v1 = 42;//局部变量
				auto f = [v1]()mutable {return ++v1; };//f可以改变它所捕获的变量的值
				v1 = 0;
				auto j = f();//j为43
				cout << j << endl;
			} 

			void static returnVal()
			{
				auto f = [](int i) {
					// 取绝对值
					return i < 0 ? -i : i;
				};

				// 错误，无法自动推断
				auto f2 = [](int i) {
					// 取绝对值
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
				// sz采用隐式值捕获的方式
				auto wa = find_if(w.begin(), w.end(), [=](const string& s) {
					return s.size() >= sz;
				});
			}

			//原版
			void static test_captureHide_biggies(std::vector<std::string>& words,
				std::vector<std::string>::size_type sz, ostream& os = cout, char c = ' ') {
				  
				// print result
				for_each(words.begin(), words.end(), [&, c](const std::string& s) {os << s << c; });
			}
			 


			//void static capture_mixed() {
			//	vector<string> words = { "the", "quick", "red", "fox","red", "the","slow" };
			//	mixed_print(words, std::cout, '_');
			//}

			//原版
			void static biggies(std::vector<std::string>& words,
				std::vector<std::string>::size_type sz, ostream &os = cout, char c = ' ') {  


				stable_sort(words.begin(), words.end(),
					[](const string& s1, const string& s2) {  return s1.size() < s2.size(); });

				// print result
				for_each(words.begin(), words.end(), [&os, c](const std::string& s) {os << s << c; });
			}

			//原版
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
				copy(foo.begin(), foo.end(), inserter(di, di.begin())); // 接收两个参数
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
				* 定义输入流迭代器
				* 只有键入ctrl+d结束输入后，后两句方可执行。
				*/
				istream_iterator<int> in_iter(std::cin);


				istream_iterator<int> eof;
				vector<int> vec;

				// 输入流迭代器作为参数给vector容器赋值
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
				std::ostream_iterator<int> iter_out(std::cout, " ");    // 每个数据输出后都输出一个空格
				std::vector<int> vec = { 1, 3, 5 };
				for (auto i : vec)
					*iter_out++ = i;    // i被写入到cout中

				for (auto i : vec)
					iter_out = i;    // 此语句和上面等价，因为*和++实际上不对iter_out做任何事情

				std::cout << std::endl;
			}

			void static iostream_ostream3() {
				std::ostream_iterator<int> iter_out(std::cout, " ");    // 每个数据输出后都输出一个空格
				std::vector<int> vec = { 1, 3, 5 };
				copy(vec.begin(), vec.end(), iter_out);
				cout << endl;
			}

			void static iostream_TestSales_item() {
				istream_iterator<TestSales_item> in_iter(cin), eof;
			 
				ostream_iterator<TestSales_item> out_iter(cout, "\n");
				//创建Sales_item对象sum，并且用in_iter内的元素初始化，接着in_iter读取下一个值
				TestSales_item sum = *in_iter++;
				//创建while循环，当in_iter关联的流没有遇到错误，并且没有到达文件末尾的时候，循环继续
				while (in_iter != eof)
				{
					//如果刚才读取的元素的isbn和sum中的Sales_data的isbn相等，那么把这个元素加到sum中，且
					//in_iter读取下一个值
					if (in_iter->isbn == sum.isbn)
					{
						sum += *in_iter++;
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



	////swap后
	//v1 = { 4,5,6,7,8,9 };
	//v2 = { 1,2,3 };
}; 
#endif
