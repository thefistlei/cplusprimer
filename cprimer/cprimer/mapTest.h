 

#ifndef MAPTEST_H 
#define MAPTEST_H
  

#include "wordTransform.h"

#include <map>
#include <set>

#include <unordered_map>
#include <unordered_set>


using std::map;
using std::set;
using std::unordered_map;

#include <string>
using std::string;

#include <utility>
using std::pair;

#include <cstddef>
using std::size_t;

#include <iostream>
using std::cin; using std::cout; using std::endl;

#include <forward_list> 
#include <iostream> 
#include <fstream>
#include <sstream>
#include <istream>

using std::string;   
 
using std::multimap;


class mapTest {
public:
	mapTest(){}

	virtual ~mapTest() {}
	 
	void static map_test1()
	{
		map<string, size_t> word_count; // empty map from string to size_t
		string word;
		while (cin >> word)
			++word_count[word];

		for (const auto& w : word_count)
			cout << w.first << " occurs " << w.second << " times" << endl;

		// get an iterator positioned on the first element
		auto map_it = word_count.cbegin();
		// compare the current iterator to the off-the-end iterator
		while (map_it != word_count.cend()) {
			// dereference the iterator to print the element key--value pairs
			cout << map_it->first << " occurs "
				<< map_it->second << " times" << endl;
			++map_it;  // increment the iterator to denote the next element
		}
	} 

	void static set_test1()
	{
		map<string, size_t> word_count; // empty map from string to size_t

		set<string> exclude = {"The", "But"};

		string word;
		while (cin >> word)
			if(exclude.find(word) == exclude.end())
				++word_count[word];

		for (const auto& w : word_count)
			cout << w.first << " occurs " << w.second << " times" << endl;

		// get an iterator positioned on the first element
		auto map_it = word_count.cbegin();
		// compare the current iterator to the off-the-end iterator
		while (map_it != word_count.cend()) {
			// dereference the iterator to print the element key--value pairs
			cout << map_it->first << " occurs "
				<< map_it->second << " times" << endl;
			++map_it;  // increment the iterator to denote the next element
		}
	}
	 
	
	void static multimap_test()
	{
		std::map<string, string> authors = { {"Joyce", "James"} };
		std::map<string, string> word_count = authors;
		std::multimap<string, string> word_count2(authors.cbegin(), authors.cend());
	 
		std::set<string> exclude = { "the", "but" };
		std::set<string> exclude1(exclude.cbegin(), exclude.cend());

		std::multiset<string> exclude2(exclude.cbegin(), exclude.cend()); 

	} 

	void static multimap_test1()
	{ 
		class Sales_data {
		public:
			Sales_data() {}

			bool operator < (const Sales_data& lhs)
			{
				return  true;
			}

			bool static compareIsbn(const Sales_data& lhs, const Sales_data& rhs)
			{
				return  true;
			}
		};  

		multiset<Sales_data, decltype(Sales_data::compareIsbn)*> bookstore(Sales_data::compareIsbn);

	}

	void static insert()
	{
		string word("dda");

		//map<string, size_t> m = { { "2", 0 } };

		map<string, size_t> word_count;
		word_count.insert({ word, 1 });//在参数列表中使用花括号初始化创建了一个pair。
		word_count.insert(make_pair(word, 1));//也可在参数列表中调用make_pair构造pair。
		word_count.insert(pair<string, size_t>(word, 1));//也可显示构造pair。
		word_count.insert(map<string, size_t>::value_type(word, 1)); //先构造一个pair类型，再构造该类型的一个新对象（对象类型为pair）。

		map<string, size_t>::iterator a = word_count.begin();
		map<string, size_t>::iterator b = ++a;

		cout << word_count.size() << endl;

		word_count.insert(a, b); 
		word_count.insert(b, {"da", 0});

		cout << word_count.size() << endl; 
	}

	void static multiInsert()
	{
		multimap<string, string> authors;
		authors.insert({ "author1", "book1" });
		authors.insert({ "author1", "book2" });
		cout << authors.size() << endl;
	}

	void static action_getData()
	{
		// map from author to title; there can be multiple titles per author
		multimap<string, string> authors;

		// add data to authors 
		authors.insert({ "Alain de Botton", "On Love" });
		authors.insert({ "Alain de Botton", "Status Anxiety" });
		authors.insert({ "Alain de Botton", "Art of Travel" });
		authors.insert({ "Alain de Botton", "Architecture of Happiness" });
		/*
		authors.insert(pair<string, string>("Alain de Botton", "On Love"));
		authors.insert(pair<string, string>("Alain de Botton", "Status Anxiety"));
		authors.insert(pair<string, string>("Alain de Botton", "Art of Travel"));
		authors.insert(pair<string, string>("Alain de Botton", "Architecture of Happiness"));
		*/
		string search_item("Alain de Botton"); // author we'll look for
		auto entries = authors.count(search_item); // number of elements
		auto iter = authors.find(search_item); // first entry for this author
		/*
		// loop through the number of entries there are for this author
		while (iter != authors.end()) {//while(entries) 
			cout << iter->second << endl; // print each title
			++iter;     // advance to the next title
			--entries;  // keep track of how many we've printed
		}	 
		*/
		// definitions of authors and search_item as above
		// beg and end denote the range of elements for this author
		for (auto beg = authors.lower_bound(search_item),
			end = authors.upper_bound(search_item);
			beg != end; ++beg)
			cout << beg->second << endl; // print each title
	 
		// definitions of authors and search_item as above
		// pos holds iterators that denote the range of elements for this key
		for (auto pos = authors.equal_range(search_item);
			pos.first != pos.second; ++pos.first)
			cout << pos.first->second << endl; // print each title
	}

	void static unorder_test1()
	{ 
		unordered_map<string, size_t> word_count;
		string word;
		while (cin >> word)
		{
			++word_count[word];
		}

		for (auto e : word_count)
			cout << e.first;

		for(auto b = word_count.begin();b!= word_count.end();b++) {
			cout << b->first;
		} 
	}

	void static unorder_test2()
	{
class Sales_data {
public:
	int n;
	Sales_data() {}
	Sales_data(int) {}

	bool operator < (const Sales_data& lhs)
	{
		return  true;
	}

	bool static compareIsbn(const Sales_data& lhs, const Sales_data& rhs)
	{
		return  true;
	}

	std::string isbn() const { return ""; }

	// how to override default hash and equality operator on key_type
	size_t static hasher(const Sales_data& sd)
	{
		return hash<string>()(sd.isbn());
	}

	bool static eqOp(const Sales_data& lhs, const Sales_data& rhs)
	{
		return lhs.isbn() == rhs.isbn();
	}

	// we'll see how to define our own operators in chapter 14
	bool operator =(const Sales_data& l)
	{
		return l.n == this->n;
	}
};

		

			// type alias using our functions in place of hash<key_type> and ==
#ifdef TYPE_ALIAS_DECLS
			using SD_multiset = unordered_multiset<Sales_data,
				decltype(hasher)*, decltype(eqOp)*>;
#else
			typedef
				unordered_multiset<Sales_data, decltype(Sales_data::hasher)*, decltype(Sales_data::eqOp)*> SD_multiset;
#endif

			// bookstore can hold multiple Sales_data with the same ISBN
			// arguments are the bucket size 
			// and pointers to the hash function and equality operator
			SD_multiset bookstore(42, Sales_data::hasher, Sales_data::eqOp);

			// use FooHash to generate the hash code; Foo must have an == operator
			//unordered_set<Sales_data, decltype(Sales_data::hasher)*> fooSet(10, Sales_data::hasher);

			// how to override just the hash function;
			// Foo must have ==
			class Foo { 
			public:
				string s;
				size_t static FooHash(const Foo& f) 
				{ 
					return hash<string>()(f.s);
				}  
			}; 
	}


	

	void static test()
	{
		//map_test1();
		//set_test1();
		//insert();
		//multiInsert();
		//action_getData();
		//unorder_test1();
		wordTransform obj;
		obj.test();
	}


	////swap后
	//v1 = { 4,5,6,7,8,9 };
	//v2 = { 1,2,3 };
}; 
#endif
