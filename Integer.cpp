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
		Integer result = *this;
		return result;
	}

	/* Takes a value and returns it as a positive */
	Integer Integer::operator+() {
		Integer result = *this;
		if (!result.posOrNeg) {
		result.posOrNeg = true;
		}
		return result;
	}

	Integer& Integer::operator+=(const Integer& i) {
		
		Integer copyOfI = Integer(i);
		int maxSize;

		// sets max size to what ever array is bigger
		if (i.value.size() >= value.size()) {
			maxSize = i.value.size() + 1;
		} else if (value.size()> i.value.size()) {
			maxSize = value.size() + 1;
		}

		// 0 pads the array
		size_t noAddI = maxSize - i.value.size();
		size_t noAddValue = maxSize - value.size(); 		
		copyOfI.value.insert(copyOfI.value.begin(), noAddI, 0);
		value.insert(value.begin(), noAddValue, 0);

		// Does the math
   		for (int x = maxSize - 1; x >= 0; x--) {
        	int digitSum = value[x] + copyOfI.value[x];
        	if (digitSum > 9) {
            	value[x] = digitSum % 10;
            	if (x > 0) {
                	value[x - 1] += digitSum / 10;
            	}
        	} else {
            	value[x] = digitSum;
        	}
    	}

		// If 0 in front gets rid of it.
    	if (value[0] == 0) {
        	value.erase(value.begin());
    	}

    	return *this;
	}


	/* Takes two values and returns the value of one value subtracted from the other */
	/* works for all types, dosent work for rhs substantially larger than lhs*/
	Integer& Integer::operator-=(const Integer& i) {
		Integer copyOfI = Integer(i);
		int maxSize;

		// sets max size to what ever array is bigger
		if (i.value.size() >= value.size()) {
			maxSize = i.value.size() + 1;
		}
		else if (value.size() > i.value.size()) {
			maxSize = value.size() + 1;
		}

		// 0 pads the array
		size_t noAddI = maxSize - i.value.size();
		size_t noAddValue = maxSize - value.size();
		copyOfI.value.insert(copyOfI.value.begin(), noAddI, 0);
		value.insert(value.begin(), noAddValue, 0);
		if (this->posOrNeg&&i.posOrNeg) {
			// Does the math
			for (int x = maxSize - 1; x >= 0; x--) {
				int digitSum = value[x] - copyOfI.value[x];
				if (digitSum < 0) {
					value[x] = digitSum % 10;
					if (x > 0) {
						value[x - 1] += digitSum / 10;
					}
				}
				else {
					value[x] = digitSum;
				}
			}
		}
		else if (this->posOrNeg && !i.posOrNeg) {
			for (int x = maxSize - 1; x >= 0; x--) {
				int digitSum = value[x] + copyOfI.value[x];
				if (digitSum < 0) {
					value[x] = digitSum % 10;
					if (x > 0) {
						value[x - 1] += digitSum / 10;
					}
				}
				else {
					value[x] = digitSum;
				}
			}
		}
		else if (!this->posOrNeg && i.posOrNeg) {
			for (int x = maxSize - 1; x >= 0; x--) {
				int digitSum = value[x] + copyOfI.value[x];
				if (digitSum < 0) {
					value[x] = digitSum % 10;
					if (x > 0) {
						value[x - 1] += digitSum / 10;
					}
				}
				else {
					value[x] = digitSum;
				}
			}
			if (this->getValue() < i.getValue()) {
				//this->posOrNeg = true;
			}
			else {
				//this->posOrNeg = false;
			}
		}
		else {
			for (int x = maxSize - 1; x >= 0; x--) {
				int digitSum = value[x] - copyOfI.value[x];
				if (digitSum < 0)digitSum *= -1;
				if (digitSum < 0) {
					value[x] = digitSum % 10;
					if (x > 0) {
						value[x - 1] += digitSum / 10;
					}
				}
				else {
					value[x] = digitSum;
				}

			}
			if (this->getValue() > i.getValue()) {
			this->posOrNeg = true;
			}
		}
		
		// If 0 in front gets rid of it.
		if (value[0] == 0) {
			value.erase(value.begin());
		}

		return *this;
	}


	/* Takes two values and returns one multiplied by the other */
	/* Not working yet but does have the idea kinda*/
	Integer& Integer::operator*=(const Integer& i) {

		int y = 0;
		Integer out;
		Integer other;
		if (this->getValue() > i.getValue()) {
			for (int x = 0;i.value.size();x++) {
				y = (i.value[x]) + (y * 10);
			}
			 other = Integer(*this);
		}
		else {
			for (int x = 0;i.value.size();x++) {
				y = this->value[x] + (y * 10);
			}
			 other = Integer(i);
		}
		for (int x = 0;x < y;x++) {
			out = out + other;
		}
		return out;
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

	// doesnt go to negative numbers, need to fix.
	// converts it to negative but doesnt set posOrNeg to negative.
	// might need to change how it is getting passed in idk.
	Integer operator+(const Integer& lhs, const Integer& rhs) {
		Integer out;
		Integer minus;
		if (lhs.posOrNeg && rhs.posOrNeg) {
			out.operator+=(lhs);
			out.operator+=(rhs);
		} else if (lhs.posOrNeg && !rhs.posOrNeg) {
			out.operator+=(lhs);
			minus.operator+=(rhs);
			out = out - minus;
		} else if (!lhs.posOrNeg && rhs.posOrNeg) {
			minus.operator+=(lhs);
			out.operator+=(rhs);
			out = out - minus;
		} else if (!lhs.posOrNeg && !rhs.posOrNeg) {
			out.operator-=(lhs);
			out.operator+=(rhs);
		}
		return out;
	}

	/* Takes two values and removes one from the other */
	/*Dosent currently work*/
	Integer operator-(const Integer& lhs, const Integer& rhs) {
		Integer out;
		Integer minus;
		if (lhs.posOrNeg && rhs.posOrNeg) {
			out.operator+=(lhs);
			out.operator-=(rhs);
		}
		else if (lhs.posOrNeg && !rhs.posOrNeg) {
			out.operator+=(lhs);
			out.operator-=(rhs);

		}
		else if (!lhs.posOrNeg && rhs.posOrNeg) {
			out.operator-=(lhs);
			out.operator-=(rhs);
		}
		else if (!lhs.posOrNeg && !rhs.posOrNeg) {
			out.operator-=(lhs);
			out.operator-=(rhs);
		}
		return out;
		}

	/* Takes two values and multiplies them together */
	Integer operator*(const Integer& lhs, const Integer& rhs) {
		Integer out;
		out.operator+=(lhs);
		out.operator*=(rhs);
		
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
		if (!lhs.posOrNeg && rhs.posOrNeg) {
			return true;
		} else if (lhs.posOrNeg && !rhs.posOrNeg) {
			return false;
		} else if (!lhs.posOrNeg && !rhs.posOrNeg) {
			return lhs.getValue() > rhs.getValue();
		} else {
			return lhs.getValue() < rhs.getValue();
		}
	}

	/* Takes two values if lhs is greater then rhs returns True, otherwise returns False */
	bool operator> (const Integer& lhs, const Integer& rhs) {
		if (lhs.posOrNeg && !rhs.posOrNeg) {
			return true;
		} else if (!lhs.posOrNeg && rhs.posOrNeg) {
			return false;
		} else if (!lhs.posOrNeg && !rhs.posOrNeg) {
			return lhs.getValue() < rhs.getValue();
		} else {
			return lhs.getValue() > rhs.getValue();
		}
	}

	/* Takes two values if rhs is less then or equal to lhs returns True, otherwise returns False */
	bool operator<=(const Integer& lhs, const Integer& rhs) {
		if (!lhs.posOrNeg && rhs.posOrNeg) {
			return true;
		} else if (lhs.posOrNeg && !rhs.posOrNeg) {
			return false; 
		} else if (!lhs.posOrNeg && ! rhs.posOrNeg) {
			return lhs.getValue() >= rhs.getValue();
		} else {
			return lhs.getValue() <= rhs.getValue();
		}
	}

	/* Takes two values if lhs is greater then or equal to rhs returns True, otherwise returns False */
	bool operator>=(const Integer& lhs, const Integer& rhs) {
		if (lhs.posOrNeg && !rhs.posOrNeg) {
			return true;
		} else if (!lhs.posOrNeg && rhs.posOrNeg) {
			return false;
		} else if (!lhs.posOrNeg && !rhs.posOrNeg) {
			return lhs.getValue() <= rhs.getValue();
		} else {
			return lhs.getValue() >= rhs.getValue();
		}
	}

	/* Takes two values returns True if they are equal */
	bool operator==(const Integer& lhs, const Integer& rhs) {
		if (lhs.posOrNeg && !rhs.posOrNeg) {
			return false;
		} else if (!lhs.posOrNeg && rhs.posOrNeg) {
			return false;
		} else {
			return lhs.getValue() == rhs.getValue();
		}
	}

	/* Takes two values returns True if they are not equal */
	bool operator!=(const Integer& lhs, const Integer& rhs) {
		if (lhs.posOrNeg && !rhs.posOrNeg) {
			return true;
		} else if (!lhs.posOrNeg && rhs.posOrNeg) {
			return true;
		} else {
			return lhs.getValue() != rhs.getValue();
		}
	}

	/* Takes two values and returns the greatest common divisor */
	Integer gcd(const Integer& a, const Integer& b) {
		if (operator==(b, Integer(0)) ) {
			return a;
		}
		return gcd(b, operator%(a, b));
	}


}
