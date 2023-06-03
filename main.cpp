/*
	Test main for Rational and Integer
*/

#include "Integer.h"
#include "Rational.h"
#include <iostream>
using namespace std;
using namespace cosc326;

int main() {

	//Integer sum;

	std::cout << "Kia ora World" << std::endl;
	cosc326::Integer myInteger;
	cosc326::Integer myIntegerCopy(myInteger);  // Create a copy of myInteger using the copy constructor	
	std::cout << myInteger << std::endl; // Print myInteger using the overloaded operator<<
	// std::cout << "eeeee" << std::endl;
	Integer a = Integer("-17");
	std::cout << a << std::endl;
	Integer b = Integer("99");
	std::cout << b << std::endl;
	Integer sum = a + b;
	std::cout << sum << std::endl;
	// std::cout << "eeeee" << std::endl;
	return 0;
}
