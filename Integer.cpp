#include "Integer.h"

namespace cosc326 {

	/* Sets the default value of Integer to 0 */
	Integer::Integer() {
		value = 0;
	}

	/* Creates a copy of Integer */
	Integer::Integer(const Integer& i) {
		value = i.value;
	}

	/* Takes in a string and passes it to int */
	Integer::Integer(const std::string& s) {
		if (s.empty()) {
			value = 0;
		} else {
			value = std::stoi(s);
			if (value > 0) {
				posOrNeg = 1;
			} else if (value < 0) {
				posOrNeg = 2;
			} else if (value == 0) {
				posOrNeg = 0;
			}
		}
	}

	Integer::~Integer() {
		value = 0;
	}

	Integer& Integer::operator=(const Integer& i) {
		return *this;
	}

	Integer Integer::operator-() const {
		Integer clone = Integer(*this);
		*this - clone;
		*this - clone;

		return Integer(*this);
	}

	Integer Integer::operator+() const {
		return Integer(*this);
	}

	Integer& Integer::operator+=(const Integer& i) {
		*this + Integer(i);
		return *this;
	}

	Integer& Integer::operator-=(const Integer& i) {
		*this - Integer(i);
		return *this;
	}

	Integer& Integer::operator*=(const Integer& i) {
		*this * Integer(i);
		return *this;
	}

	Integer& Integer::operator/=(const Integer& i) {
		*this / Integer(i);
		return *this;
	}

	Integer& Integer::operator%=(const Integer& i) {
		*this % Integer(i);
		return *this;
	}

	Integer operator+(const Integer& lhs, const Integer& rhs) {
		Integer out;
		out.operator+=(rhs);
		out.operator+=(lhs);
		return out;
	}

	Integer operator-(const Integer& lhs, const Integer& rhs) {
		Integer out;
		out.operator-=(rhs);
		out.operator-=(lhs);
		return out;	}

	Integer operator*(const Integer& lhs, const Integer& rhs) {
		return lhs;
	}

	Integer operator/(const Integer& lhs, const Integer& rhs) {
		return lhs;
	}

	Integer operator%(const Integer& lhs, const Integer& rhs) {
		return lhs;
	}


	std::ostream& operator<<(std::ostream& os, const Integer& i) {
		return os;
	}

	std::istream& operator>>(std::istream& is, Integer& i) {
		return is;
	}

	bool operator<(const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator> (const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator<=(const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator>=(const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator==(const Integer& lhs, const Integer& rhs) {
		return true;
	}

	bool operator!=(const Integer& lhs, const Integer& rhs) {
		return true;
	}


	Integer gcd(const Integer& a, const Integer& b) {
		return a;
	}




}
