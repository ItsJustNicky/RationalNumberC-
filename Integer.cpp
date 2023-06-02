#include "Integer.h"

namespace cosc326 {

	/* Sets the default value of Integer to 0 */
	Integer::Integer() {
		value = {0};
	}

	/* Creates a copy of Integer */
	Integer::Integer(const Integer& i) {
		value = i.value;
	}

	/* Takes in a string and passes each individual item to a Integer Vector */
	Integer::Integer(const std::string& s) {
		std::string temp;
		if (s.empty()) {
			value[0] = 0;
		} else {
			posOrNeg = true;
			if(s[0] == '+') {
				posOrNeg = true;
				temp = s.substr(1);
			} else if (s[0] == '-') {
				posOrNeg = false;
				temp = s.substr(1);
			}
			for (char i : temp) {
				value.push_back(std::stoi(std::string(1, i)));
			}
		}
	}

	/* Deconstructor */
	Integer::~Integer() {
	}

	/* Takes a value and returns what it is equal to*/
	Integer& Integer::operator=(const Integer& i) {
		//if (posOrNeg == true) {
		value =  i.value;
		//} else if (posOrNeg == false) {
		//	value = i.value;
		//	value.insert(value.begin(), "-");
		//}
		return *this;
	}

	/* Takes a value and returns it as a negative */
	Integer Integer::operator-() {
		this->posOrNeg=false;
		return -Integer(*this);
	}

	/* Takes a value and returns it as a positive */
	Integer Integer::operator+() {
		this->posOrNeg=true;
		return Integer(*this);
	}

	/* Takes a value and adds it to the value */
	Integer& Integer::operator+=(const Integer& i) {
		if(value.size() < i.value.size()){
			int iValueLength = i.value.size();
			int valueLength = value.size();
			
			while (valueLength < iValueLength + 1) {
				valueLength += 1;
				value.insert(value.begin(), 0);
			}
		}	
		for (size_t x = value.size()-1; x > 0; x--) {
				if (value[x]+i.value[x] > 9) {
					value[x-1] = value[x-1] + 1;
					value[x]=value[x]+i.value[x]-10;
				}
				value[x]=value[x]+i.value[x];
    	}

		if (value[0] == 0) {
			value.erase(value.begin());
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
		Integer left = lhs;
		Integer right = rhs;
		return left += right;
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
    	os<< "helloworld";
	//os << i.getValue();
	//if (i.posOrNeg == false) {
    //    os << '-';
    //}
    //for (const auto& digit : i.value) {
     //   os << digit;
    //}
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
