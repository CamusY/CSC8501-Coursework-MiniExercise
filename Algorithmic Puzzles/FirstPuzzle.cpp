#include <iostream>
#include <stdio.h>
#include "FixedPoints.h"

// For testing purposes only
// #include <cmath> 

using namespace std;


// At first, I tried to use binary search method to find the square root of a number
long long binarySearchSqrtWithNoFloats(long long n) {
    if (n < 0) return -1; // Error for negative numbers
    if (n == 0 || n == 1) return n;

    long long start = 1, end = n, ans = 0;
    while (start <= end) {
        long long mid = start + (end - start) / 2;

        if (mid <= n / mid) { // To prevent overflow
            start = mid + 1;
            ans = mid;
        }
        else end = mid - 1;
    }
    return ans;
}

//But I found that Newton's method is faster and more elegant, and it won't overflow as easily as binary search method.
long long NewtonSqrtWithNoFloats(long long n) {
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
So I created a FixedPoint class to handle fixed-point arithmetic.
It's in the file FixedPoints.h.
*/

/*
And while writing code below, I realized that if the 40-year-old computer does not support floating-point arithmetic.
It not supposed to smoothly handle long long integers either.
So I tried to shorten the long long integers to long.
*/

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

istream& operator>>(istream& is, FixedPoint& fp) {
    string input;
    is >> input;

    long integerPart = 0;
    long decimalPart = 0;
    bool isNegative = false;
    bool afterDecimal = false;
    long divisor = 1;

    // Parse the input string
    for (int i = 0; i < input.length(); ++i) {
        char c = input[i];

        if (i == 0 && c == '-') {
            isNegative = true;
            continue;
        }
        if (c == '.') {
            afterDecimal = true;
            continue;
        }

        long digit = c - '0';

        if (afterDecimal) {
            decimalPart = decimalPart * 10 + digit;
            divisor *= 10;
        }
        else integerPart = integerPart * 10 + digit;

    }

    //combine integer and decimal parts
    long long finalRawValue = static_cast<long long>(integerPart) * fp.SCALE;

    if (decimalPart > 0)
        finalRawValue += (static_cast<long long>(decimalPart) * fp.SCALE) / divisor;

    fp.rawValue =static_cast<long>(isNegative ? -finalRawValue : finalRawValue);

    return is;
}

// Newton's method for square root by using FixedPoint
FixedPoint FixedNewtonSqrtWithNoFloats(const FixedPoint& n) {
    if (n.rawValue < 0) return FixedPoint(-1); // Error for negative numbers
    if (n.rawValue == 0) return n; // 0 or 1

    FixedPoint x = (n / FixedPoint(2)) + FixedPoint(1); // Initial guess: n/2 + 1

    // At first, I tried to use while(x * x > n) like the integer version, however, it cost too many iterations
    // So I changed to a for loop with a fixed number of iterations to ensure convergence
    for (int i = 0; i < 20; ++i) {
        x = (x + n / x) / FixedPoint(2);
    }
    return x;
}


int main() {
    long long number;
    cout << "Enter a non-negative integer: ";
    cin >> number;
    cout << "Square root of " << number << " is: ";
    cout << "using Newton's method: " << NewtonSqrtWithNoFloats(number) << endl;
    cout << "using Binary Search method: " << binarySearchSqrtWithNoFloats(number) << endl;

    cout << "Now, let's test the FixedPoint class and its square root function." << endl;

    FixedPoint a, b;

    cout << "Enter a non-negative fixed-point number without decimal part (e.g., 3): ";
    cin >> a;
    cout << "You entered: " << a << endl;
    cout << "Enter a non-negative fixed-point number with decimal part (e.g., 3.14): ";
    cin >> b;
    cout << "You entered: " << b << endl;

    cout << "Testing calculations with FixedPoint:" << endl;
    cout << a << " + " << b << " = " << (a + b) << endl;
    cout << a << " - " << b << " = " << (a - b) << endl;
    cout << a << " * " << b << " = " << (a * b) << endl;
    cout << a << " / " << b << " = " << (a / b) << endl;

    cout << "Testing comparison operators with FixedPoint:" << endl;
    cout << a << " <= " << b << " : " << (a <= b) << endl;
    cout << a << " < " << b << " : " << (a < b) << endl;
    cout << a << " >= " << b << " : " << (a >= b) << endl;
    cout << a << " > " << b << " : " << (a > b) << endl;
    cout << a << " == " << b << " : " << (a == b) << endl;

    cout << "Testing square root function with FixedPoint:" << endl;
    cout << "Square root of " << a << " is: ";
    cout << "using Newton's method:" << FixedNewtonSqrtWithNoFloats(a) << endl;
    cout << "Square root of " << b << " is: ";
    cout << "using Newton's method:" << FixedNewtonSqrtWithNoFloats(b) << endl;


    return 0;
}
