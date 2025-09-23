#include <iostream>
using namespace std;

int main() {
    int maxVal;            // <-- uninitialised
    int count; cin >> count;
    for (int i = 0; i < count; ++i) {
        int val; cin >> val;
        if (val > maxVal)  // compare against garbage on first iteration
            maxVal = val;
    }
    cout << "Max: " << maxVal << "\n";
}

/*
These are two safe initialization strategies for maxVal:
    1. Initialize maxVal to the smallest possible integer value, or 0.
        int maxVal = std::numeric_limits<int>::min();
        int maxVal = 0; // if input values are non-negative
        
    Final code with the first strategy:
        #include <iostream>
        #include <limits>
        using namespace std;

        int main() {
            int maxVal = std::numeric_limits<int>::min();
            // or int maxVal = 0; if input values are non-negative
            int count; cin >> count;
            // if (count <= 0) {
            //    cerr << "No values provided.\n";
            //    return 1; 
            //}
            for (int i = 0; i < count; ++i) {
                int val; cin >> val;
                if (val > maxVal)
                    maxVal = val;
            }
            cout << "Max: " << maxVal << "\n";
        }

    2. Read the first value outside the loop and send it to maxVal, but count must be > 0.
        int val; cin >> val;
        int maxVal = val;
        for (int i = 1; i < count; ++i) { // start loop from 1
            cin >> val;
            if (val > maxVal)
                maxVal = val;
        }
    Final code with the second strategy:
        #include <iostream>
        using namespace std;

        int main() {
            int count; cin >> count;
            if (count <= 0) {
                cerr << "No values provided.\n";
                return 1;
            }
            int val; cin >> val;
            int maxVal = val;
            for (int i = 1; i < count; ++i) {
                cin >> val;
                if (val > maxVal)
                    maxVal = val;
            }
            cout << "Max: " << maxVal << "\n";
        }

Minimum watch list of variables for debuggers and why:
    maxVal - to ensure it is correctly updated and holds the maximum value
    count - to verify the number of iterations
    val - to check each input value whether being compared
*/