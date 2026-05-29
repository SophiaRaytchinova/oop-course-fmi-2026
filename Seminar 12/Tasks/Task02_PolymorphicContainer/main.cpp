#include <iostream>
#include "PolymorphicContainer.hpp"

class Base {
public:
    virtual ~Base() = default;
    virtual void f() const = 0;
    virtual std::unique_ptr<Base> clone() const = 0;
};

class A : public Base {
public:

    void f() const override {
        std::cout << "A::f()" << std::endl;
    }

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<A>(*this);
    }
};

class B : public Base {
public:

    void f() const override {
        std::cout << "B::f()" << std::endl;
    }

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<B>(*this);
    }
};

class C: public Base {
public:

    void f() const override {
        std::cout << "C::f()" << std::endl;
    }

    std::unique_ptr<Base> clone() const override {
        return std::make_unique<C>(*this);
    }
};

int main() {
    PolymorphicContainer<Base> container;
    A a;
    std::unique_ptr<B> bPtr = std::make_unique<B>();

    container.pushBack(a);
    container.pushBack(bPtr);
    container.pushBack(std::make_unique<C>());

    for (const auto& basePtr: container) {
        basePtr->f();
    }
}