#include "Rational.h"
#include "Integer.h"

namespace cosc326 {

	/* Sets the default value of Integer to 0 */
	Rational::Rational() {
		posOrNeg = true;
		value.push_back(0);
		dec.push_back(0);
	}

	/* Creates a copy of Integer */
	Rational::Rational(const Rational& r) {
		value = r.value;
	}

	/* Takes in a string and passes each individual item to a Integer Vector */
	Rational::Rational(const std::string& s) {
		std::string temp;
		bool isDec = false;
		if (s.empty()) {
			posOrNeg = true;
			value.push_back(0);
		}
		else {
			if (s[0] == '-') {
				posOrNeg = false;
				temp = s.substr(1);
			}
			else if (s[0] == '+') {
				posOrNeg = true;
				temp = s.substr(1);
			}
			else {
				temp = s;
				posOrNeg = true;
			}
			for (char c : temp) {
				if (c == '.') {
					isDec = true;
				}
				if (std::isdigit(c)&&!isDec) {
					value.push_back(c - '0');
				}if (std::isdigit(c)&&isDec) {
					dec.push_back(c - '0');
				}
				else {
					// Handle error: invalid input string
					value.clear();
					dec.clear();
					posOrNeg = true;
					value.push_back(0);
					dec.push_back(0);
					break;
				}
			}
		}
	}

	Rational::Rational(const Integer& a) {
		value = a.getValue();
	}

	Rational::Rational(const Integer& a, const Integer& b) {
		Integer top = Integer(a);
		top /= b;
		Integer bottom = Integer(a);
		bottom %= b;
		value = top.getValue();
		Integer bClone = b;
		int decConversion=bottom.concatenateIntegers(bottom.getValue());
		int bConversion = bClone.concatenateIntegers(bClone.getValue());
		decConversion = decConversion / bConversion;
		std::string strNumber = std::to_string(decConversion);
		Integer out = (strNumber);
		dec = out.getValue();
	}

	Rational::Rational(const Integer& a, const Integer& b, const Integer& c) {
		Integer top = Integer(b);
		top /= c;
		Integer bottom = Integer(b);
		bottom %= c;
		value = a.getValue();
		Integer cClone = c;
		int decConversion = bottom.concatenateIntegers(bottom.getValue());
		int bConversion = cClone.concatenateIntegers(cClone.getValue());
		decConversion = decConversion / bConversion;
		std::string strNumber = std::to_string(decConversion);
		Integer out = (strNumber);
		dec = out.getValue();
	}

	/* Deconstructor */
	Rational::~Rational() {
	}

	/* Takes a value and set value to that value */
	Rational& Rational::operator=(const Rational& r) {
		posOrNeg = r.posOrNeg;
		value.clear();
		value = r.value;
		dec = r.dec;
		return *this;
	}

	/* Takes a value and returns it as a negative */
	Rational Rational::operator-() const {
		Rational copy(*this);
		copy.posOrNeg = !copy.posOrNeg;
		return copy;
	}

	/* Takes a value and returns it as a positive */
	Rational Rational::operator+() const {
    	return *this;
	}

	Rational& Rational::operator+=(const Rational& r) {
		posOrNeg = r.posOrNeg;
		value.clear();
		//value += r.value;
		//dec += r.dec;
		return *this;
	}

	Rational& Rational::operator-=(const Rational& r) {
		return *this;
	}

	Rational& Rational::operator*=(const Rational& r) {
		return *this;
	}

	Rational& Rational::operator/=(const Rational& r) {
		return *this;
	}

	Rational operator+(const Rational& lhs, const Rational& rhs) {
		return lhs;
	}

	Rational operator-(const Rational& lhs, const Rational& rhs) {
		return lhs;
	}

	Rational operator*(const Rational& lhs, const Rational& rhs) {
		return lhs;
	}

	Rational operator/(const Rational& lhs, const Rational& rhs) {
		return lhs;
	}

	std::ostream& operator<<(std::ostream& os, const Rational& i) {
		return os;
	}
	std::istream& operator>>(std::istream& is, Rational& i) {
		return is;
	}

	bool operator<(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator> (const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator<=(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator>=(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator==(const Rational& lhs, const Rational& rhs) {
		return true;
	}

	bool operator!=(const Rational& lhs, const Rational& rhs) {
		return true;
	}

}
