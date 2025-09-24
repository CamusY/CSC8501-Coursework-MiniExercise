#include <iostream>
#include <stdio.h>

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
How can a system without floating-point support represent a number like 3.14?



*/

int main() {
    long long number;
    cout << "Enter a non-negative integer: ";
    cin >> number;
    cout << "Square root of " << number << " is: ";
    cout << "using Newton's method: " << NewtonSqrtWithNoFloats(number) << endl;
    cout << "using Binary Search method: " << binarySearchSqrtWithNoFloats(number) << endl;
    return 0;
}
