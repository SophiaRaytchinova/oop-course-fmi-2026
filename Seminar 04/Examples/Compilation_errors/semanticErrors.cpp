#include <iostream>

class X {
private:
    int x = 0;
};

int main() {
    X obj;
    std::cout << obj.x; // semantic error, trying to access a private member

    int num = "abc"; // semantic error, assigning string to int
}
