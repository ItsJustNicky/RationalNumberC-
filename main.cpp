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
	Integer a = Integer("1");
	std::cout << a << std::endl;
	Integer b = Integer("3");
	std::cout << b << std::endl;
	
	//Integer sum2 = sum * a;
	//if (a <= b)std::cout << a << std::endl;
	//a /= b;
	//std::cout << a << std::endl;
	Integer sum = a*b;
	std::cout << sum << std::endl;
	//std::cout << sum2 << std::endl;
	//bool hmm = a == b;
	//std::cout << "----" << std::endl;
	//std::cout << hmm << std::endl;
	// std::cout << "eeeee" << std::endl;
	return 1;
}
