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
		// Sets positive to true if empty
    	if (s.empty()) {
        	posOrNeg = true;
        	value.push_back(0);
    	} else {
			// Sets negative if starts with - and removes -
			if (s[0] == '-') {
				posOrNeg = false;
				temp = s.substr(1);
			// Sets positive if starts with + and removes +
			} else if (s[0] == '+') {
				posOrNeg = true;
				temp = s.substr(1);
			} else {
				temp = s;
				posOrNeg = true;
			}
			// Converts the string into an array
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
		posOrNeg = i.posOrNeg;
		value.clear();
		value = i.value;
		
		return *this;
	}

	/* Takes a value and returns it as a negative */
	Integer Integer::operator-() {

		this->posOrNeg = false;
		return *this;
	}

	/* Takes a value and returns it as a positive */
	Integer Integer::operator+() {
		Integer result = *this;
		if (!result.posOrNeg) {
		result.posOrNeg = true;
		}
		return result;
	}

	/* Takes two values and returns the value of the two number added together */
	Integer& Integer::operator+=(const Integer& i) {

		// Initialises variables 
		Integer copyOfI = Integer(i);
		int maxSize;
		bool less = false;
		bool zeroFlip = false;
		Integer clone;

		// Checks if value is less then i
		if (*this < i && !this->posOrNeg && i.posOrNeg) {
			less = true;
			clone = *this;
			*this = i;
			clone.posOrNeg = true;
		}

		// Checks if value and i are the same 
		if (*this == i && !this->posOrNeg && i.posOrNeg) {
			zeroFlip = true;
		}

		// sets max size to what ever array is bigger
		if (i.value.size() >= value.size()) {
			maxSize = i.value.size() + 1;
		} else if (value.size() > i.value.size()) {
			maxSize = value.size() + 1;
		}

		// 0 pads the array
		size_t noAddI = maxSize - i.value.size();
		size_t noAddValue = maxSize - value.size();
		copyOfI.value.insert(copyOfI.value.begin(), noAddI, 0);
		value.insert(value.begin(), noAddValue, 0);


		// If both of the values are positive does simple addition.
		if (this->posOrNeg && i.posOrNeg) {
			for (int x = maxSize - 1; x >= 0; x--) {
				int digitSum = value[x] + copyOfI.value[x];
				if (digitSum > 9) {
					value[x] = digitSum % 10;
					if (x > 0) {
						value[x - 1] += digitSum / 10;
					}
				}
				else {
					value[x] = digitSum;
				}
			}

		// If both numbers are negative does simple addition and does not flip the sign.
		} else if (!this->posOrNeg && !i.posOrNeg) {
			for (int x = maxSize - 1; x >= 0; x--) {
				int digitSum = value[x] + copyOfI.value[x];
				if (digitSum > 9) {
					value[x] = digitSum % 10;
					if (x > 0) {
						value[x - 1] += digitSum / 10;
					}
				}
				else {
					value[x] = digitSum;
				}
			}

		//If the first value is positive and the second value is negative preforms subtraction.
		} else if (this->posOrNeg && !i.posOrNeg) {
			Integer posI = (i);
			posI.posOrNeg = true;
			for (int i = 0;i < value.size();i++) {
				if (value[0] == 0 && value.size() != 1) {
					value.erase(value.begin());
				}
			}

			// Checks if value is less then i and will need convert to negative
			bool small = false;
			if (*this < posI) {
				small = true;
				copyOfI = *this;
				*this = i;

			}
			// Does the math if value is not less then i
			if (!small) {
				for (int x = maxSize - 1; x >= 0; x--) {
					int digitSum = value[x] - copyOfI.value[x];

					 if (digitSum < 0) {
						value[x] = 9;
						if (x > 0) {
							value[x - 1]--;
						}
					}
					else {
						value[x] = digitSum;
					}
				}
			// Does the math if value is less then i
			} else {
				while (value.size() != copyOfI.value.size()) {
					copyOfI.value.insert(copyOfI.value.begin(), 0);
				}
				for (int x = value.size() - 1; x >= 0; x--) {
					int digitSum = value[x] - copyOfI.value[x];
					if (digitSum < 0) {
						value[x] = 10 + digitSum % 10;
						if (x > 0) {
							value[x - 1]--;
						}
					}
					else {
						value[x] = digitSum;
					}
				}
				this->posOrNeg = false;
			}

		// If the first value is negative and the second value is positive, needs to preform
		} else if (!this->posOrNeg && i.posOrNeg) {
			// If value is not less then i
			if (!less) {
				for (int x = maxSize - 1; x >= 0; x--) {
					int digitSum = value[x] - copyOfI.value[x];
					if (value[0] < 0) {
						posOrNeg = true;
					}
					if (digitSum < 0) {
						value[x] = digitSum + 10;
						value[x - 1] = value[x - 1] - 1;
					}
					else {
						value[x] = digitSum;
					}
				}
				if (zeroFlip)this->posOrNeg = true;
			}
			// If value is less then i
			else {
				this->posOrNeg = true;
				value.erase(value.begin());
				*this -= clone;
			}
		}

		// If there are still 0 in front from the 0 padding gets rid of it
		for (int i = 0;i < value.size();i++) {
			if (value[0] == 0 && value.size() != 1) {
				value.erase(value.begin());
			}
		}
		// Retuns the new number
		return *this;
	}

	/* Takes two values and returns the value of one value subtracted from the other */
	/* needs RHS check for overloading 1 still */
	Integer& Integer::operator-=(const Integer& i) {
		// Initialises variables 
		Integer copyOfI = Integer(i);
		int maxSize;
		bool small = false;

		// Checks if value is less then i
		if (*this < i && this->posOrNeg && i.posOrNeg) {
			small = true;
			copyOfI = *this;
			*this = i;
		}

		// sets max size to what ever array is bigger
		if (i.value.size() >= value.size()) {
			maxSize = i.value.size() + 1;
		} else if (value.size() > i.value.size()) {
			maxSize = value.size() + 1;
		}

		// 0 pads the array
		size_t noAddI = maxSize - i.value.size();
		size_t noAddValue = maxSize - value.size();
		copyOfI.value.insert(copyOfI.value.begin(), noAddI, 0);
		value.insert(value.begin(), noAddValue, 0);
		
		// Checks if both value and i are positive
		if (this->posOrNeg&&i.posOrNeg) {
			// Does the math if value is greater then i
			if (!small) {
				for (int x = maxSize - 1; x >= 0; x--) {
					int digitSum = value[x] - copyOfI.value[x];
					if (digitSum < 0) {
						value[x] = 9;
						if (x > 0) {
							value[x - 1]--;
						}
					}
					else {
						value[x] = digitSum;
					}
				}
			}
			// Does the math if i is greater then value
			else {
				for (int x = 0;x < i.value.size()-1;x++) {
					copyOfI.value.insert(copyOfI.value.begin(), 0);
				}
				for (int x = maxSize - 1; x >= 0; x--) {
					int digitSum = value[x] - copyOfI.value[x];
					if (digitSum < 0) {
						value[x] = 10+digitSum % 10;
						if (x > 0) {
							value[x - 1]--;
						}
					}
					else {
						value[x] = digitSum;
					}
				}
				this->posOrNeg = false;
			}
		}

		// Checks if value is positive and i is negative then does math
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
		// Checks if value is negative and i is positive
		} else if (!this->posOrNeg && i.posOrNeg) {
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

			/*  Following lines need to be deleted */
			if (this->getValue() < i.getValue()) {
				//this->posOrNeg = true;
			}
			else {
				//this->posOrNeg = false;
			}
		
		// if both values are negative do the math
		} else {
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
		for (int i = 0;i < value.size();i++) {
			if (value[0] == 0&&value.size()!=1) {
				value.erase(value.begin());
			}
		}

		// returns the output
		return *this;
	}

	/* Takes two values and returns one multiplied by the other */
	Integer& Integer::operator*=(const Integer& i) {
	
		// Initialises the values
		Integer y = Integer("1");
		Integer one = Integer("1");
		Integer out;
		Integer other;
		Integer og;

		// Checks if value or i is greater. Sets the greater one to other and the lesser one to og
		if (*this > i) {	
			 other = Integer(*this);
			 og = Integer(i);
			 other.posOrNeg = true;
		} else {
			 other = Integer(i);
			 og = Integer(*this);
			 other.posOrNeg = true;
		}

		out = other;
		while (y!=og) {
			out += other;
			y+=one;
		}

		// If one of the values is negative and the other is positive sets posOrNeg to false otherwise sets posOrNeg to to true
		if (!this->posOrNeg&&i.posOrNeg || !i.posOrNeg&&this->posOrNeg) {
			this->posOrNeg = false;
		}
		else {
			this->posOrNeg = true;
		}

		// returns the output
		*this = out;
		return *this;
	}

	/* Takes two values and returns one divided by the other */
	Integer& Integer::operator/=(const Integer& i) {
		
		// Checks if i is greater then value
		if (i > *this) {
			Integer zero = Integer("0");
			this->posOrNeg = true;
			*this = zero;
			return *this;
		}

		// Initialises and sets variables
		Integer x = Integer(i);
		Integer iClone = Integer(i);
		iClone.posOrNeg = true;
		x.posOrNeg = true;
		Integer y = Integer(*this);
		Integer count = Integer("0");
		Integer one = Integer("1");
		
		while (x <= y) {
			x += iClone;
			count+=one;
		}
		
		*this = count;

		// If one of the values is negative and the other is positive sets posOrNeg to false otherwise sets posOrNeg to to true
		if (!this->posOrNeg && i.posOrNeg || !i.posOrNeg && this->posOrNeg) {
			this->posOrNeg = false;
		}
		else {
			this->posOrNeg = true;
		}
		return *this;
	}

	/* Takes two values and return the remainder */
	Integer& Integer::operator%=(const Integer& i) {
		Integer zero = Integer("0");
		Integer clone = *this;
		clone /= i;

		// If value and i is zero returns zero
		if (*this == zero||i ==zero) {
			*this = zero;
			return zero;

		// If both of the variables are not equal to zero does math
		} else {
			Integer x = Integer(i);
			Integer y = (*this);
			Integer one = Integer("1");
			while (x <= y) {
				x += i;
				if (x == y) {
					*this = zero;
					return *this;
				}
			}
			if (x > *this) {
				x -= i;
			}
			*this -=x;

			// If One of this or i is positive and the other is negative sets the output to negative otherwise sets the output to positive
			if (!this->posOrNeg && i.posOrNeg || !i.posOrNeg && this->posOrNeg) {
				this->posOrNeg = false;
			} else {
				this->posOrNeg = true;
			}

			if (this->value[0] == 0 && this->value.size() >= 2) {
				this->value.erase(this->value.begin());
			}

			// returns the output
			return *this;
		}
	}

	/* Takes two values and preforms addition */
	Integer operator+(const Integer& lhs, const Integer& rhs) {
		Integer out;
		Integer minus;

		// Performs addition if both lhs and rhs are positive
		if (lhs.posOrNeg && rhs.posOrNeg) {
			out.operator+=(lhs);
			out.operator+=(rhs);
		
		// Performs subtraction if one of the lhs or rhs are negative
		} else if (lhs.posOrNeg && !rhs.posOrNeg) {
			out.operator+=(lhs);
			minus.operator+=(rhs);
			out = out - minus;	
		} else if (!lhs.posOrNeg && rhs.posOrNeg) {
			minus.operator+=(lhs);
			out.operator+=(rhs);
			out = out - minus;
		
		// Performs addition if both lhs and rhs are negative
		} else if (!lhs.posOrNeg && !rhs.posOrNeg) {
			out.operator-=(lhs);
			out.operator+=(rhs);
		}

		// Returns the output
		return out;
	}

	/* Takes two values and removes one from the other */
	Integer operator-(const Integer& lhs, const Integer& rhs) {
		Integer out;
		Integer minus;

		// If both lhs and rhs are positive adds lhs and subtracts rhs
		if (lhs.posOrNeg && rhs.posOrNeg) {
			out.operator+=(lhs);
			out.operator-=(rhs);

		// If one of lhs or rhs is positive and the other is negative subtracts both lhs and rhs
		} else if (lhs.posOrNeg && !rhs.posOrNeg) {
			out.operator-=(lhs);
			out.operator-=(rhs);
		} else if (!lhs.posOrNeg && rhs.posOrNeg) {
			out.operator-=(lhs);
			out.operator-=(rhs);
		
		// If both lhs and rhs are negative subtracts both lhs and rhs
		} else if (!lhs.posOrNeg && !rhs.posOrNeg) {
			out.operator-=(lhs);
			out.operator-=(rhs);
		}

		// Returns the output
		return out;
	}

	/* Takes two values and multiplies them together */
	Integer operator*(const Integer& lhs, const Integer& rhs) {
		Integer out("1");
		out*=(lhs);
		out*=(rhs);
		
		return out;
	}

	/* Takes two values and divides one by the other*/
	Integer operator/(const Integer& lhs, const Integer& rhs) {
		Integer out= Integer("0");
		Integer cloneLhs = (lhs);
		Integer cloneRhs = (rhs);

		// updates whether or not output should be positive or negative
		if (!lhs.posOrNeg && rhs.posOrNeg) {
			out.posOrNeg = false;
			cloneLhs.posOrNeg = true;
		} else if (lhs.posOrNeg && !rhs.posOrNeg) {
			out.posOrNeg = false;
			cloneRhs.posOrNeg = true;
		} else {
			out.posOrNeg = true;
			cloneLhs.posOrNeg = true;
			cloneRhs.posOrNeg = true;
		}

		// Calls addition and division
		out.operator+=(cloneLhs);
		out.operator/=(cloneRhs);
		
		// returns the output
		return out;
	}

	/* Takes two values and finds the remainder */
	Integer operator%(const Integer& lhs, const Integer& rhs) {
		Integer out= Integer("1");
		out.operator+=(lhs);
		out.operator%=(rhs);
		return out;
	}

	/* Allows for Integers to outputted to a stream */
	std::ostream& operator<<(std::ostream& os, const Integer& i) {
	if(i.getValue().empty() == false) {
		// If the number if negative puts a '-' in front of it
		if (i.posOrNeg == false) {
			os << '-';
		}
		// If the number is positive doesn't put an operation in front of it
		for (const auto& digit : i.getValue()) {
			os << digit;
		}
	} else {
		// If blank outputs 0
		os << '0';
	}

	// Returns the output
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
		std::ostringstream oss1;
		std::ostringstream oss2;

		// Convert the vector of digits to string
		for (int digit : lhs.getValue()) {
			oss1 << digit;
		}
		for (int digit : rhs.getValue()) {
			oss2 << digit;
		}

		std::string str1 = oss1.str();
		std::string str2 = oss2.str();

		// If lhs is negative and rhs is positive returns true
		if (!lhs.posOrNeg && rhs.posOrNeg) {
			return true;
		}

		// If rhs is positive and rhs is negative returns false
		else if (lhs.posOrNeg && !rhs.posOrNeg) {
			return false;
		}

		// If they are both either positive or both negative
		// Compare the string representations
		if (str1.length() != str2.length()) {
			return str1.length() < str2.length();
		}

		// returns 1 if str1 is less then str2 else returns false
		return str1 < str2;
	}

	/* Takes two values if lhs is greater then rhs returns True, otherwise returns False */
	bool operator> (const Integer& lhs, const Integer& rhs) {
		std::ostringstream oss1;
		std::ostringstream oss2;

		// Convert the vector of digits to string
		for (int digit : lhs.getValue()) {
			oss1 << digit;
		}
		for (int digit : rhs.getValue()) {
			oss2 << digit;
		}

		std::string str1 = oss1.str();
		std::string str2 = oss2.str();

		// If lhs is negative and rhs is positive returns false
		if (!lhs.posOrNeg && rhs.posOrNeg) {
			return false;
		}

		// If rhs is positive and rhs is negative returns true
		else if (lhs.posOrNeg && !rhs.posOrNeg) {
			return true;
		}

		// If they are both either positive or both negative
		// Compare the string representations
		if (str1.length() != str2.length()) {
			return str1.length() > str2.length();
		}

		// returns 1 if str1 is greater then str2 else returns false
		return str1 > str2;

	}

	/* Takes two values if rhs is less then or equal to lhs returns True, otherwise returns False */
	bool operator<=(const Integer& lhs, const Integer& rhs) {
		std::ostringstream oss1;
		std::ostringstream oss2;

		// Convert the vector of digits to string
		for (int digit : lhs.getValue()) {
			oss1 << digit;
		}
		for (int digit : rhs.getValue()) {
			oss2 << digit;
		}

		std::string str1 = oss1.str();
		std::string str2 = oss2.str();

		// If lhs is negative and rhs is positive returns true
		if (!lhs.posOrNeg && rhs.posOrNeg) {
			return true;

		// If lhs is positive nad rhs is negative returns false
		} else if (lhs.posOrNeg && !rhs.posOrNeg) {
			return false;
		}

		// Compare the string representations
		if (str1.length() != str2.length()) {
			return str1.length() <= str2.length();
		}

		// Returns 1 if str1 is less or equal to str2 else returns 0
		return str1 <= str2;
	}



	/* Takes two values if lhs is greater then or equal to rhs returns True, otherwise returns False */
	bool operator>=(const Integer& lhs, const Integer& rhs) {
		std::ostringstream oss1;
		std::ostringstream oss2;

		// Convert the vector of digits to string
		for (int digit : lhs.getValue()) {
			oss1 << digit;
		}
		for (int digit : rhs.getValue()) {
			oss2 << digit;
		}

		std::string str1 = oss1.str();
		std::string str2 = oss2.str();

		// If lhs is negative and rhs is positive returns false
		if (!lhs.posOrNeg && rhs.posOrNeg) {
			return false;

		// If lhs is positive nad rhs is negative returns true
		} else if (lhs.posOrNeg && !rhs.posOrNeg) {
			return true;
		}

		// Compare the string representations
		if (str1.length() != str2.length()) {
			return str1.length() >= str2.length();
		}

		// Returns 1 if str2 is less or equal to str1 else returns 0
		return str1 >= str2;
	}

	/* Takes two values returns True if they are equal */
	bool operator==(const Integer& lhs, const Integer& rhs) {
		std::ostringstream oss1;
		std::ostringstream oss2;

		// Convert the vector of digits to string
		for (int digit : lhs.getValue()) {
			oss1 << digit;
		}
		for (int digit : rhs.getValue()) {
			oss2 << digit;
		}

		std::string str1 = oss1.str();
		std::string str2 = oss2.str();

		// If lhs is negative and rhs is positive or lhs is positive and rhs is negative return false
		if (!lhs.posOrNeg && rhs.posOrNeg) {
			return false;
		} else if (lhs.posOrNeg && !rhs.posOrNeg) {
			return false;
		}

		// Compare the string representations
		if (str1.length() != str2.length()) {
			return false;
		}

		// If str1 is equal to str2 returns 1 else returns 0
		return str1 == str2;
	}

	/* Takes two values returns True if they are not equal */
	bool operator!=(const Integer& lhs, const Integer& rhs) {
		std::ostringstream oss1;
		std::ostringstream oss2;

		// Convert the vector of digits to string
		for (int digit : lhs.getValue()) {
			oss1 << digit;
		}
		for (int digit : rhs.getValue()) {
			oss2 << digit;
		}

		std::string str1 = oss1.str();
		std::string str2 = oss2.str();

		// If lhs is negative and rhs is positive or lhs is positive and rhs is negative return true
		if (!lhs.posOrNeg && rhs.posOrNeg) {
			return true;
		} else if (lhs.posOrNeg && !rhs.posOrNeg) {
			return true;
		}

		// Compare the string representations
		if (str1.length() != str2.length()) {
			return true;
		}

		// If str1 is not equal to str2 returns 1 else returns 0
		return str1 != str2;
	}

	/* Takes two values and returns the greatest common divisor */
	Integer gcd(const Integer& a, const Integer& b) {
		Integer div;
		
		// If a is greater to b set div to b else set div to a
		if (a > b) {
			div = b;
		} else {
			div = a;
		}

		// Initialises variables
		Integer out= Integer("0");
		Integer zero = Integer("0");
		Integer one = Integer("1");
		
		// performs math while go is true
		bool go = true;
		while (go){
			if (div == zero)go = false;
			if (a % div == zero && b%div==zero) {
				out = div;
				go = false;
			}
			div -= one;
		}

		// Returns the output
		return out;
	}

}
