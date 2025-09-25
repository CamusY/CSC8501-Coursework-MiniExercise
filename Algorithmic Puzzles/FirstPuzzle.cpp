#include <iostream>
#include <stdio.h>
#include <cmath> // For testing purposes only

using namespace std;

long long binarySearchSqrtWithNoFloats(long long n) {
    if (n < 0) return -1; // Error for negative numbers
    if (n == 0 || n == 1) return n;

    long long start = 1, end = n, ans = 0;
    while (start <= end) {
        long long mid = start + (end - start) / 2;

        if (mid <= n / mid) { // To prevent overflow
            start = mid + 1;
            ans = mid;
        } else end = mid - 1;
    }
    return ans;
}

long long NewtonSqrtWithNoFloats(long long n){
    if (n < 0) return -1; // Error for negative numbers
    if (n == 0 || n == 1) return n;

    long long x = n;
    
    while (x * x > n) x = (x + n / x) / 2;
    
    return x;
}

/*
Usually, it is the end of this puzzle, but I want to dig deeper.
These functions above only find the integer part of the square root.
How can we find the decimal part without using floating-point arithmetic?
How can a system without floating-point support represent a number like 3.14?
I tried to use a scaling factor, like 65536(2^16), to represent decimal numbers as integers.
For example, 3.14 would be represented as 205783 (3.14 * 65536).
Then, I can perform integer arithmetic on these scaled values.
BUT, the most challenging part is to do the calculation of these scaled values
without causing overflow and while maintaining precision.
*/

/*
And while writing code below, I realized that if the 40-year-old computer does not support floating-point arithmetic.
It not supposed to smoothly handle long long integers either.
So I tried to shorten the long long integers to long.
*/

class FixedPoint {
public:
    static constexpr int SCALE_FACTOR = 16; // 2^16
    static constexpr long SCALE = 1L << SCALE_FACTOR; // 65536

    long rawValue;
    
    // Default constructor
    FixedPoint() : rawValue(0) {}

    // Constructor from integer part
    FixedPoint(long integerPart) : rawValue(integerPart * SCALE) {}

    // Test double constructor (only for testing purposes)
    FixedPoint(double doubleValueForTestOnly ) : rawValue(round(doubleValueForTestOnly*SCALE)) {}

private:
    // Private constructor from raw value
    explicit FixedPoint(long rawValue) : rawValue(rawValue) {}

public:
    // add
    FixedPoint operator+();


    //Add a friendly function to print the FixedPoint value (for testing purposes)
    friend ostream& operator<<(ostream& os, const FixedPoint& fp);


};

ostream& operator<<(ostream& os, const FixedPoint& fp) {
    //get integer part
    os << (fp.rawValue >> fp.SCALE_FACTOR);
    //get decimal part
    os << ".";
    long decimalPart = fp.rawValue & (fp.SCALE - 1);
    //print decimal part with leading zeros
    for (int i = 0; i < FixedPoint::SCALE_FACTOR / 4; ++i) {
        decimalPart *= 10;
        os << (decimalPart >> FixedPoint::SCALE_FACTOR);
        decimalPart &= (FixedPoint::SCALE - 1);
    }
    return os;
};


 

int main() {
    long long number;
    cout << "Enter a non-negative integer: ";
    cin >> number;
    cout << "Square root of " << number << " is: ";
    cout << "using Newton's method: " << NewtonSqrtWithNoFloats(number) << endl;
    cout << "using Binary Search method: " << binarySearchSqrtWithNoFloats(number) << endl;
    return 0;
}
