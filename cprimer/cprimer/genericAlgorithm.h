 

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

using std::string;  
using std::vector;
using std::forward_list;
using std::list;

using std::cin; using std::cout; using std::endl;

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

	void static test()
	{
		test_unique_copy();
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
