int* makeVal() {
    int x = 42;
    return &x;      // ❌ returns address of a dead stack variable
}

int& pick(bool b) {
    int a = 1, c = 2;
    return b ? a : c;  // ❌ returns reference to dead locals
}

/*
These are two fixes for makeVal:
first, return by value:
return x;
second, RAII pointer:
#include <memory>
return std::make_unique<int>(x);
Final code after first fix:
int makeVal() {
    int x = 42;
    return x;
}

Final code after the second fixes:
#include <memory>
std::unique_ptr<int> makeVal() {
    int x = 42;
    return std::make_unique<int>(x); // returns a unique_ptr to a heap object
}

Final code after rewrite of pick to make it safe and communicates ownership:
int pick(bool b) {
    int a = 1, c = 2;
    return b ? a : c;
}
*/