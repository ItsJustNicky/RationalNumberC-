
// Most compilers understand the once pragma, but just in case...
#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

namespace cosc326 {

	class Integer {

	private:
		vector <int> value;
		std::string stringValue;
		
	public:
		
		 // true is positive, false is negative 
		bool posOrNeg;
	    const std::vector<int>& getValue() const {
			return value;
        }
		int concatenateIntegers(const std::vector<int>& nums) {
			std::string concatenatedStr;

			for (int num : nums) {
				concatenatedStr += std::to_string(num);
			}

			return std::stoi(concatenatedStr);
		}
		Integer();                             // Integer i; // Default constructor declaration 
		Integer(const Integer& i);             // Integer j(i); // Copy integer constructor declaration
		Integer(const std::string& s);         // Integer k("123"); //  Constructor that takes a string of digits

		~Integer();

		Integer& operator=(const Integer& i);  // j = i;

		// Unary operators
		Integer operator-();                   // -j;
		Integer operator+();                   // +j;

		// Arithmetic assignment operators
		Integer& operator+=(const Integer& i); // j += i;
		Integer& operator-=(const Integer& i); // j -= i;
		Integer& operator*=(const Integer& i); // j *= i;
		Integer& operator/=(const Integer& i); // j /= i;
		Integer& operator%=(const Integer& i); // j %= i;

		// lhs < rhs -- a 'friend' means operator isn't a member, but can access the private parts of the class.
		// You may need to make some other functions friends, but do so sparingly.
		friend bool operator<(const Integer& lhs, const Integer& rhs);
		//friend std::ostream& operator<<(std::ostream& os, const Integer& i);
	private:
		// Can add internal storage or methods here
	};

	// Binary operators
	Integer operator+(const Integer& lhs, const Integer& rhs); // lhs + rhs;
	Integer operator-(const Integer& lhs, const Integer& rhs); // lhs - rhs;
	Integer operator*(const Integer& lhs, const Integer& rhs); // lhs * rhs;
	Integer operator/(const Integer& lhs, const Integer& rhs); // lhs / rhs;
	Integer operator%(const Integer& lhs, const Integer& rhs); // lhs % rhs;

	std::ostream& operator<<(std::ostream& os, const Integer& i);  // std::cout << i << std::endl;
	std::istream& operator>>(std::istream& is, Integer& i);        // std::cin >> i;

	bool operator> (const Integer& lhs, const Integer& rhs); // lhs > rhs
	bool operator<=(const Integer& lhs, const Integer& rhs); // lhs <= rhs
	bool operator>=(const Integer& lhs, const Integer& rhs); // lhs >= rhs
	bool operator==(const Integer& lhs, const Integer& rhs); // lhs == rhs
	bool operator!=(const Integer& lhs, const Integer& rhs); // lhs != rhs

	Integer gcd(const Integer& a, const Integer& b);  // i = gcd(a, b);
};

#endif
