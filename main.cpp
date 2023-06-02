/*
	Test main for Rational and Integer
*/

#include "Integer.h"
#include "Rational.h"
#include <iostream>
using namespace std;
using namespace cosc326;

int main() {

	Integer sum;

	std::cout << "Kia ora World" << std::endl;
	//cosc326::Integer myInteger;
	//cosc326::Integer myIntegerCopy(myInteger);  // Create a copy of myInteger using the copy constructor	
	std::cout << "eeeee" << std::endl;
	Integer a = Integer("5");
	Integer b = Integer("10");
	std::cout << "AHHHHH" << std::endl;
	sum = a + b;
	std::cout << "eeeee" << std::endl;
	return 0;
}
