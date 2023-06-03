#include "Integer.h"

namespace cosc326 {

	/* Sets the default value of Integer to 0 */
	Integer::Integer() {
		posOrNeg = true;
		value.push_back(0);
	}

	/* Creates a copy of Integer */
	Integer::Integer(const Integer& i) {
		value = i.value;
	}

	/* Takes in a string and passes each individual item to a Integer Vector */
	/* Copied straight from chatGPT might wanna change this at some point */
	Integer::Integer(const std::string& s) {
		std::string temp;
    	if (s.empty()) {
        	posOrNeg = true;
        	value.push_back(0);
    	} else {
			if (s[0] == '-') {
				posOrNeg = false;
				temp = s.substr(1);
			} else if (s[0] == '+') {
				posOrNeg = true;
				temp = s.substr(1);
			} else {
				temp = s;
				posOrNeg = true;
			}
        	for (char c : temp) {
            	if (std::isdigit(c)) {
                	value.push_back(c - '0');
            	} else {
                	// Handle error: invalid input string
                	value.clear();
                	posOrNeg = true;
                	value.push_back(0);
                	break;
            	}
        	}
    	}
	}

	/* Deconstructor */
	Integer::~Integer() {
	}

	/* Takes a value and set value to that value */
	Integer& Integer::operator=(const Integer& i) {
		value.clear();
		value = i.value;
		return *this;
	}

	/* Takes a value and returns it as a negative */
	Integer Integer::operator-() {
		this->posOrNeg=false;
		return -Integer(*this);
	}

	/* Takes a value and returns it as a positive */
	Integer Integer::operator+() {
		Integer result = *this;
		if (!result.posOrNeg) {
		result.posOrNeg = true;
		}
		return result;
	}

	/* Takes a value and adds it to the value */
	Integer& Integer::operator+=(const Integer& i) {

    	size_t maxLength = std::max(value.size(), i.value.size());
    	value.resize(maxLength, 0); // Resize the vector if necessary

		// check which list is greater, set max size to that one

		// blank pad the one that is smaller so they are the same size

		// add one blank 0 to the front to them both


    	int carry = 0;
    	for (size_t x = 0; x < maxLength; ++x) {

			// if the sum is greater then 9 add 1 to value[x-1]

        	int digitSum = value[x] + carry; // Add carry from the previous digit
        	if (x < i.value.size()) {
            	digitSum += i.value[x];
        	}

        	value[x] = digitSum % 10; // Store the result in the current digit
        	carry = digitSum / 10; // Calculate the carry for the next digit
    	}

    	if (carry > 0) {
        	value.push_back(carry); // If there is a carry after all digits, add a new digit
    		}
		
    	return *this;
	}

	/* Takes two values and returns the value of one value subtracted from the other */
	Integer& Integer::operator-=(const Integer& i) {
			Integer copyOfi = Integer(i);
				if(value.size() < i.value.size()){
			int iValueLength = i.value.size();
			int valueLength = value.size();
			
			while (valueLength < iValueLength + 1) {
				valueLength += 1;
				value.insert(value.begin(), 0);
			}
		}else if(value.size() < i.value.size()){
			int iValueLength = i.value.size();
			int valueLength = value.size();
			
			while (valueLength > iValueLength + 1) {
				iValueLength += 1;
				copyOfi.value.insert(copyOfi.value.begin(), 0);
			}
		}	
		for (size_t x = value.size()-1; x > 0; x--) {
				if (value[x]<copyOfi.value[x] ) {
					value[x-1] = value[x-1] -1;
					value[x]=value[x]+10-copyOfi.value[x];
				}else{
					value[x]=value[x]-copyOfi.value[x];
    		}
		}		

		if (value[0] == 0) {
			value.erase(value.begin());
		}

		return *this;
	}

	/* Takes two values and returns one multiplied by the other */
	Integer& Integer::operator*=(const Integer& i) {
	//	value *= i.value;
		return *this;
	}

	/* Takes two values and returns one divided by the other */
	Integer& Integer::operator/=(const Integer& i) {
	//	value /= i.value;
		return *this;
	}

	/* Takes two values and return the remainder */
	Integer& Integer::operator%=(const Integer& i) {
	//	value %= i.value;
		return *this;
	}

	/* Takes two values and preforms addition */
	Integer operator+(const Integer& lhs, const Integer& rhs) {
		Integer out;
		out.operator+=(rhs);
		out.operator+=(lhs);
		return out;
	}

	/* Takes two values and removes one from the other */
	Integer operator-(const Integer& lhs, const Integer& rhs) {
		Integer out;
		out.operator-=(rhs);
		out.operator-=(lhs);
		return out;	
		}

	/* Takes two values and multiplies them together */
	Integer operator*(const Integer& lhs, const Integer& rhs) {
		Integer out;
		out.operator*=(rhs);
		out.operator*=(lhs);
		return out;
	}

	/* Takes two values and divides one by the other*/
	Integer operator/(const Integer& lhs, const Integer& rhs) {
		Integer out;
		out.operator/=(rhs);
		out.operator/=(lhs);
		return out;
	}

	/* Takes two values and finds the remainder */
	Integer operator%(const Integer& lhs, const Integer& rhs) {
		Integer out;
		out.operator%=(rhs);
		out.operator%=(lhs);
		return out;
	}

	/* Allows for Integers to outputted to a stream */
	std::ostream& operator<<(std::ostream& os, const Integer& i) {
	if(i.getValue().empty() == false) {
		if (i.posOrNeg == false) {
			os << '-';
		}
		for (const auto& digit : i.getValue()) {
			os << digit;
		}
	} else {
		os << '0';
		}
	return os;
}

	
	/* Allows for Integers to be inputted to a stream */
	std::istream& operator>>(std::istream& is, Integer& i) {
		int value;
		is >> value;
		return is;
	}



	/* Takes two values if rhs is greater then lhs returns True, otherwise returns False */
	bool operator<(const Integer& lhs, const Integer& rhs) {
	//	return lhs.getValue() < rhs.getValue();
	}

	/* Takes two values if lhs is greater then rhs returns True, otherwise returns False */
	bool operator> (const Integer& lhs, const Integer& rhs) {
	//	return lhs.getValue() > rhs.getValue();
	}

	/* Takes two values if rhs is less then or equal to lhs returns True, otherwise returns False */
	bool operator<=(const Integer& lhs, const Integer& rhs) {
	//	return lhs.getValue() <= rhs.getValue();
	}

	/* Takes two values if lhs is greater then or equal to rhs returns True, otherwise returns False */
	bool operator>=(const Integer& lhs, const Integer& rhs) {
	//	return lhs.getValue() >= rhs.getValue();
	}

	/* Takes two values returns True if they are equal */
	bool operator==(const Integer& lhs, const Integer& rhs) {
	//	return lhs.getValue() == rhs.getValue();
	}

	/* Takes two values returns True if they are not equal */
	bool operator!=(const Integer& lhs, const Integer& rhs) {
	//	return lhs.getValue() != rhs.getValue();
	}

	/* Takes two values and returns the greatest common divisor */
	Integer gcd(const Integer& a, const Integer& b) {
		if (operator==(b, Integer(0)) ) {
			return a;
		}
		return gcd(b, operator%(a, b));
	}


}
