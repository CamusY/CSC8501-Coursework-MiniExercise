#pragma once
#include <iostream>

class FixedPoint {
private:
    // Private constructor from raw value
    struct RawTag {};
    FixedPoint(long raw, RawTag) : rawValue(raw) {}

public:
    static constexpr int SCALE_FACTOR = 16; // 2^16
    static constexpr long SCALE = 1L << SCALE_FACTOR; // 65536

    long rawValue;

    // Default constructor
    FixedPoint() : rawValue(0) {}
	// Constructor from integer
	FixedPoint(int integerPart) : rawValue(static_cast<long>(integerPart)* SCALE) {}
	// Constructor from long
	FixedPoint(long integerPart) : rawValue(integerPart* SCALE) {}
    FixedPoint(const FixedPoint& other) : rawValue(other.rawValue) {}
    static FixedPoint FromRawValue(long raw) {
        return FixedPoint(raw, RawTag{});
    }

    FixedPoint operator+(const FixedPoint& other) const {
        return FixedPoint::FromRawValue(rawValue + other.rawValue);
    }
    FixedPoint operator-(const FixedPoint& other) const {
        return FixedPoint::FromRawValue(rawValue - other.rawValue);
    }
    FixedPoint operator*(const FixedPoint& other) const {
        long long temp = static_cast<long long>(rawValue) * other.rawValue;
        return FixedPoint::FromRawValue(static_cast<long>(temp >> SCALE_FACTOR));
    }
    FixedPoint operator/(const FixedPoint& other) const {
        if (other.rawValue == 0) {
            return FixedPoint::FromRawValue(0x7FFFFFFF);
        }
        long long temp = (static_cast<long long>(rawValue) << SCALE_FACTOR) / other.rawValue;
        return FixedPoint::FromRawValue(static_cast<long>(temp));
    }


    // comparison operators
    bool operator<=(const FixedPoint& other) const {
        return this->rawValue <= other.rawValue;
    }
    bool operator<(const FixedPoint& other) const {
        return this->rawValue < other.rawValue;
    }
    bool operator>=(const FixedPoint& other) const {
        return this->rawValue >= other.rawValue;
    }
    bool operator>(const FixedPoint& other) const {
        return this->rawValue > other.rawValue;
    }
    bool operator==(const FixedPoint& other) const {
        return this->rawValue == other.rawValue;
    }

	//due to the limitation of time, I didn't implement other operators like +=, -=, *=, /=, !=, etc.
	//but the above operators are enough for this puzzle.
	//and rest of the operators are easy to implement.
	//rest of the code is in FixedPoints.cpp

};