 

#ifndef ORDERCONTAINER_H 
#define ORDERCONTAINER_H
  
#include <forward_list> 
#include <iostream> 
#include <fstream>
#include <sstream>
#include <istream>

using std::string;  
using std::vector;


using std::cin; using std::cout; using std::endl;

class orderContainer {
public:
	orderContainer(){}

	virtual ~orderContainer() {}
	 
	void static test()
	{
		forward_list<int> vi = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		auto prev = vi.before_begin();
		auto curr = vi.begin();
		while (curr != vi.end())
		{
			if (*curr % 2)
			{
				curr = vi.erase_after(prev);
			}
			else {
				prev = curr;
				curr++;
			}
		}

		auto curr2 = vi.begin();
		while (curr2 != vi.end()) {
			cout << *curr2;
			curr2++;
		}
	} 

	void static testSwap()
	{
		vector<int> v1 = { 1,2,3 };
		vector<int> v2 = { 4,5,6,7,8,9 };
		swap(v1, v2);
		int i = 0;
	}
	////swapºó
	//v1 = { 4,5,6,7,8,9 };
	//v2 = { 1,2,3 };
}; 
#endif
