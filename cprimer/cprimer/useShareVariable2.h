 

#ifndef USESHAREVARIABLE2_H 
#define USESHAREVARIABLE2_H
  
#include <iostream>

#include "shareVariable.h"
 
extern int nShare;

class useShareVariable2 {
public:
	void static test() {
		std::cout << nShare;
	}
};
#endif
