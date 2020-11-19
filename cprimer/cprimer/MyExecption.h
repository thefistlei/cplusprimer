 

#ifndef MYEXCEPTION_H 
#define MYEXCEPTION_H
  

using namespace std;

#include <exception>

class MyExecption : public exception 
{
public:
	MyExecption(){}

	virtual ~MyExecption() {}

	//const char * whate() const throw ()
	//{
	//	return "C++ Exception";
	//}

}; 
#endif
