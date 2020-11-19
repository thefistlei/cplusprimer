 

#ifndef VECTORTEST_H 
#define VECTORTEST_H
  
#include <vector> 
#include <iostream> 

using std::string;  
using std::vector;


using std::cin; using std::cout; using std::endl;

class vectorTest {
public:
	vectorTest(){}

	virtual ~vectorTest() {}
	 
	void static test()
	{  
		vector<unsigned> grades;
		// count the number of grades by clusters of ten:
		// 0--9, 10--19, . . . 90--99, 100
		unsigned scores[11] = {};  // 11 buckets, all value initialized to 0
		unsigned grade;
		while (cin >> grade) {  
			if (grade <= 100)
				// increment the counter for the current cluster
				++scores[grade / 10];
			grades.push_back(grade);
		}
		cout << "grades.size = " << grades.size() << endl;

		for (auto g : grades)  // for every element in grades
			cout << g << " ";
		cout << endl;

		for (auto i : scores)       // for each counter in scores
			cout << i << " ";       // print the value of that counter
		cout << endl;
	}
}; 
#endif
