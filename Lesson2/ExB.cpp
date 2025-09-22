
int x = 40; int y = 60; int z = x + y;
double a1 = z / 2.0; // average?
bool f = a1 > 50.0;  // pass flag?

/*
    Rename variables to meaningful names:
    int x -> const int leftScore
    int y -> const int rightScore
    int z -> int sum
    double a1 -> double average
    bool f -> bool isPassing

    final refactored code:
    const int leftScore = 40;
    const int rightScore = 60;
    int sum = leftScore + rightScore;
    double average = sum / 2.0;
    bool isPassing = average > 50.0;
*/