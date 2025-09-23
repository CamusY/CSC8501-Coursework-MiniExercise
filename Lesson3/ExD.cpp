int count = 10;
for (int i = 0; i < count; ++i) {
    int count = i;    // ❌ shadows outer 'count'
    // ...
}

/*
Final code after elimination of shadowing, mark immutable variables as 'const':
const int count = 10;
for (const int i = 0; i < count; ++i) {
    const int currentIndex = i;
    // ...
}

*/