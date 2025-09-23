double average;
int n; cin >> n;
int sum = 0;
for (int i = 0; i < n; ++i) {
    int v; cin >> v;
    sum += v;
}
average = sum / static_cast<double>(n);
cout << "Average: " << average << "\n";

/*
These variables can be const:
    n - input size
    v - input value
    average - computed average
These variables can be narrowed scope without hurting readability:
    n - should be > 0 to
These are edge cases must be guard:
    n should be > 0 to avoid division by zero
Final code with improvements:
    const int n; cin >> n;
    if (n <= 0) {
        cerr << "Invalid input size\n";
        return 1;
    }
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        const int v; cin >> v;
        sum += v;
    }
    const double average = sum / static_cast<double>(n);
    cout << "Average: " << average << "\n";

*/