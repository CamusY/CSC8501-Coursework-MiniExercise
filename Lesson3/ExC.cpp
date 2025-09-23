int main() {
    int* p = new int{5};
    delete p;
    std::cout << *p << "\n";   // ❌ use-after-free

    int* q = new int[3]{1,2,3};
    delete q;                 // ❌ wrong deallocator (should be delete[])
    // ...
}

/*
Code after correct the manual version and refactor to unique_ptr:
int main() {
    int* p = new int{5};
    std::unique_ptr<int> up(p);
    std::cout << *up << "\n";

    std::unique_ptr<int[]> uq(new int[3]{1,2,3});
    // ...
}
*/