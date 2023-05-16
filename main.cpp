/*
	Test main for Rational and Integer
*/

#include <iostream>
using namespace std;

#include "Integer.h"
#include "Rational.h"

using namespace cosc326;

int main() {

	std::cout << "Kia ora World" << std::endl;
	cosc326::Integer myInteger;
		cosc326::Integer myIntegerCopy(myInteger);  // Create a copy of myInteger using the copy constructor	

	std::cout << "Value of myInteger: " << myInteger.getValue() << std::endl;
	std::cout << "Value of myIntegerCopy: " << myIntegerCopy.getValue() << std::endl;

	return 0;
}
