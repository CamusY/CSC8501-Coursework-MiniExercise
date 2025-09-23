#include <iostream>
using namespace std;

int main() {
    int n;                    // 1)
    if (true) {
        int n = 3;            // 2) (shadows outer n)
        int* p = new int(n);  // 3) pointer + heap object
        *p += 1;              // 4)
        cout << *p << "\n";
        delete p;             // 5)
    }                         // 6)
    cout << n << "\n";        // 7)
}

/*

At the end of the inner block (5), p is released,
at the end of the inner block (6), the inner n is released.
If outer n is not initialized, its value is undefined at (7).
Final code after rewrite of outer n to safely initialize it and make sure no shadowing occurs:
int main() {
    int n = 0;                // initialize outer n
    if (true) {
        int inner_n = 3;      // renamed to avoid shadowing
        int* p = new int(inner_n);
        *p += 1;
        cout << *p << "\n";
        delete p;
    }
    cout << n << "\n";
}

*/