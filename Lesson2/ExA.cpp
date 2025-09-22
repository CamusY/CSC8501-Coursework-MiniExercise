// Compute average and pass/fail (threshold 50)
#include <iostream>
using namespace std;

int main() {
    int a = 78;        // exam 1
    int b = 85;        // exam 2
    int c = 92;        // exam 3
    int tmp = a;       // <-- suspicious
    int total = 0;
    total = a + b + c;
    double avg;        // <-- declared early, uninitialised
    avg = total / 3.0;
    bool t = true;     // <-- defaulted, then overwritten
    if (avg < 50.0) { t = false; }
    cout << "Average: " << avg << "  passed? " << (t ? "yes" : "no") << endl;
    return 0;
}