#pragma once

class FixedPoint {
public:
    static constexpr int SCALE_FACTOR = 16; // 2^16
    static constexpr long SCALE = 1L << SCALE_FACTOR; // 65536

    long rawValue;

    // Default constructor
    FixedPoint() : rawValue(0) {}

    // Constructor from integer part
    FixedPoint(long integerPart) : rawValue(integerPart* SCALE) {}

    FixedPoint(const FixedPoint& other) {
		this->rawValue = other.rawValue;
    }


    // Test double constructor (only for testing purposes)
    // FixedPoint(double doubleValueForTestOnly ) : rawValue(round(doubleValueForTestOnly*SCALE)) {}

//private:
    // Private constructor from raw value
    // explicit FixedPoint(long rawValue) : rawValue(rawValue) {}

public:
    // add
    FixedPoint operator+(const FixedPoint& other) const {
        return FixedPoint(this->rawValue + other.rawValue);
    }
    // subtract
    FixedPoint operator-(const FixedPoint& other) const {
        return FixedPoint(this->rawValue - other.rawValue);
    }
    // multiply
    FixedPoint operator*(const FixedPoint& other) const {
        long long temp = static_cast<long long>(this->rawValue) * other.rawValue;
        return FixedPoint(static_cast<long>(temp >> SCALE_FACTOR));
    }
    // divide
    FixedPoint operator/(const FixedPoint& other) const {
        long long temp = (static_cast<long long>(this->rawValue) << SCALE_FACTOR) / other.rawValue;
        return FixedPoint(static_cast<long>(temp));
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

    //Add a friendly function to print the FixedPoint value (for testing purposes)
    //friend ostream& operator<<(ostream& os, const FixedPoint& fp);


};