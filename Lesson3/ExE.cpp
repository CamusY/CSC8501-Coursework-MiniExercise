#include <iostream>
#include <string>
struct Trace {
    std::string name;
    Trace(std::string n): name(std::move(n)) { std::cout << "+" << name << "\n"; }
    ~Trace() { std::cout << "-" << name << "\n"; }
};

int main(){
    Trace a("a");
    {
        Trace b("b");
        {
            Trace c("c");
        }
    }
}

/*

The exact output order of this program is(annotated where each object destroyed):

step 1: +a
step 2: +b
step 3: +c
step 4: -c  // c goes out of scope here
step 5: -b  // b goes out of scope here
step 6: -a  // a goes out of scope here
destroyed in reverse order of creation
a is created first, but destroyed last
b is created second, but destroyed second last
c is created last, but destroyed first
*/