//first safe initialization strategy
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

//second safe initialization strategy
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
/*
These are robust checks to each strategy so the program behaves predictably for:
if n == 0 (no inputs), then the program should not attempt to read any values.
if an input value is negative, the program should validate each input value and handle it appropriately. A check can be added inside the loop to test if an input value is negative.
A final check should be added after the loop to handle the edge case where all provided inputs were invalid.
Final code with the first strategy:
    #include <iostream>
    #include <limits>
    using namespace std;

    int main() {
        int maxVal = std::numeric_limits<int>::min();
        int count; cin >> count;
        if (count <= 0) {
            cerr << "No values provided.\n";
            return 1;
        }
        int valid_inputs_found = 0;
        for (int i = 0; i < count; ++i) {
            int val; cin >> val;
            if (val < 0) {
                cerr << "Warning: Input " << val << " is negative and will be ignored.\n";
                continue; // Skip to the next iteration.
            }
            valid_inputs_found++;
            if (val > maxVal)
                maxVal = val;
        }
        if (valid_inputs_found == 0) {
            cerr << "No valid inputs found.\n";
            return 1;
        }
        cout << "Max: " << maxVal << "\n";
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
        int maxVal;
        bool first_valid_found = false;

        for (int i = 0; i < count; ++i) {
            int val; cin >> val;
            if (val < 0) {
                cerr << "Warning: Input " << val << " is negative and will be ignored.\n";
                continue; // Skip to the next iteration.
            }
            if (!first_valid_found) {
                maxVal = val;
                first_valid_found = true;
            } else if (val > maxVal)
                maxVal = val;
        }
        if (!first_valid_found) {
            cerr << "No valid inputs found.\n";
            return 1;
        }
        cout << "Max: " << maxVal << "\n";
    }
*/
