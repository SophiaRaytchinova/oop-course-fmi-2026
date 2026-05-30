# Open/Closed Principle

Кодът трябва да е отворен за разширяване, но затворен за промяна.

Тоест, когато добавяме нова функционалност, е по-добре да добавим нов код, вместо да променяме вече работещия стар код.

---

## Лош пример

```cpp
#include <iostream>
#include <string>

class DiscountCalculator {
public:
    double calculate(const std::string& customerType, double price) {
        if (customerType == "regular") {
            return price * 0.05;
        }

        if (customerType == "vip") {
            return price * 0.15;
        }

        if (customerType == "student") {
            return price * 0.10;
        }

        return 0.0;
    }
};
```

### Какъв е проблемът?

Ако добавим нов тип клиент, например `employee`, трябва да променим класа `DiscountCalculator`.

Това може да доведе до грешки, защото пипаме вече съществуващ и работещ код.

---

## Добър пример

```cpp
#include <iostream>

class DiscountStrategy {
public:
    virtual ~DiscountStrategy() = default;
    virtual double calculate(double price) const = 0;
};

class RegularDiscount : public DiscountStrategy {
public:
    double calculate(double price) const override {
        return price * 0.05;
    }
};

class VipDiscount : public DiscountStrategy {
public:
    double calculate(double price) const override {
        return price * 0.15;
    }
};

class StudentDiscount : public DiscountStrategy {
public:
    double calculate(double price) const override {
        return price * 0.10;
    }
};

class DiscountCalculator {
public:
    double calculate(double price, const DiscountStrategy& strategy) const {
        return strategy.calculate(price);
    }
};
```

### Използване

```cpp
int main() {
    DiscountCalculator calculator;
    VipDiscount vipDiscount;

    double discount = calculator.calculate(100.0, vipDiscount);

    std::cout << "Discount: " << discount << std::endl;
}
```

Ако искаме нова отстъпка, просто добавяме нов клас:

```cpp
class EmployeeDiscount : public DiscountStrategy {
public:
    double calculate(double price) const override {
        return price * 0.20;
    }
};
```

Не променяме `DiscountCalculator`.

---

## С какво помага?

Open/Closed Principle помага кодът да бъде:

- по-лесен за разширяване;
- по-безопасен за промяна;
- по-лесен за тестване;
- по-малко зависим от големи `if`/`switch` конструкции;
- по-подреден при добавяне на нови функционалности.

---

## Обобщение

Вместо да пишем код, който постоянно трябва да се редактира, правим структура, която позволява добавяне на ново поведение чрез нови класове.

Добра идея е да използваме този принцип, когато очакваме дадена логика да има различни варианти — например различни отстъпки, начини на плащане, типове известия или правила за валидация.
