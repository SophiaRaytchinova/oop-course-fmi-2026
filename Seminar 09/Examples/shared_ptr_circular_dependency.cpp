#include <iostream>
#include <memory>
#include <string>

struct Person {
    std::string name;
    std::weak_ptr<Person> partner; // non-owning reference

    Person(std::string n) : name(std::move(n)) {
        std::cout << "Person created: " << name << '\n';
    }

    ~Person() {
        std::cout << "Person destroyed: " << name << '\n';
    }
};

int main() {
    auto alice = std::make_shared<Person>("Alice");
    auto bob = std::make_shared<Person>("Bob");

    alice->partner = bob;
    bob->partner = alice;

    std::cout << "alice.use_count = " << alice.use_count() << '\n';
    std::cout << "bob.use_count = " << bob.use_count() << '\n';
}
