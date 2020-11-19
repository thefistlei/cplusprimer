 

#ifndef STRINGTEST_H 
#define STRINGTEST_H
  
#include <string> 
#include <iostream> 

using std::string;  
using std::getline;


using std::cin; using std::cout; using std::endl;

class stringTest {
public:
	stringTest(){}

	virtual ~stringTest() {}

	void static getLine() {
		string line;

		// read input a line at a time until end-of-file
		while (getline(cin, line))
			cout << line << endl; 
	} 

	void static getCin() {
		string line;

		// read input a line at a time until end-of-file
		while (cin >> line)
			cout << line << endl;
	} 
}; 
#endif
