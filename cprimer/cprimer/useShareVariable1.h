 

#ifndef USESHAREVARIABLE1_H 
#define USESHAREVARIABLE1_H
  
#include <iostream>

#include "shareVariable.h"

extern int nShare = 1;// 指定变量名字、类型

class useShareVariable1 {
public:
	void static test() {
		std::cout << nShare;
	}
};
#endif
