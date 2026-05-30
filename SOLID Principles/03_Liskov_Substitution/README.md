# Liskov Substitution Principle

Ако един клас наследява друг, наследникът трябва да може да се използва навсякъде, където се очаква базовият клас, без програмата да се счупи.

С други думи: наследяването трябва да е логически правилно, не само синтактично.

- Всеки базов клас трябва да бъде заменяем с всеки един от неговите наследници

- Подкласовете трябва да задоволяват синтактичните и поведенческите очаквания на своите родителски класове

- Трябва да можем да използваме указатели / референции от базовия клас, без да се интересуваме към обект от кой конкретен наследник са насочени

---

## Лош пример

Имаме базов клас `Bird`, в който има метод `fly()`:

```cpp
#include <iostream>
#include <stdexcept>

class Bird {
public:
    virtual ~Bird() = default;

    virtual void fly() = 0;
};
```

Сега имаме `Eagle` и `Sparrow`, които наистина могат да летят:


```cpp
class Eagle : public Bird {
public:
    void fly() override {
        std::cout << "Eagle is flying\n";
    }
    void makeSound() const override {
        std::cout << "Eagle is making sound...\n";
    }
};
```

```cpp
class Sparrow : public Bird {
public:
    void fly() override {
        std::cout << "Sparrow is flying\n";
    }
    void makeSound() const override {
        std::cout << "Sparrow is making sound...\n";
    }
};
```

Но имаме и `Penguin`:

```cpp
class Penguin : public Bird {
public:
    void fly() override {
        throw std::runtime_error("Penguins cannot fly");
    }
    void makeSound() const override {
        std::cout << "Penguin is making sound...\n";
    }
};
```

### Какъв е проблемът?

На теория `Penguin` е птица, но в нашия код `Bird` обещава, че всяка птица може да лети.

Това води до проблем:

```cpp
void makeBirdFly(Bird& bird) {
    bird.fly();
}
```

```cpp
int main() {
    Sparrow sparrow;
    Penguin penguin;

    makeBirdFly(sparrow); // OK
    makeBirdFly(penguin); // Runtime error
}
```

`Penguin` наследява `Bird`, но не може коректно да го замести, защото не поддържа поведението `fly()`.

Това нарушава Liskov Substitution Principle.

---

## Добър пример

Решението е да не слагаме `fly()` в базовия клас `Bird`, защото не всички птици могат да летят.

Вместо това добавяме междинен абстрактен клас `FlyingBird`.

```cpp
#include <iostream>

class Bird {
public:
    virtual ~Bird() = default;

    virtual void makeSound() const = 0;
};
```

`FlyingBird` представлява само птици, които могат да летят:

```cpp
class FlyingBird : public Bird {
public:
    virtual void fly() = 0;
};
```

Сега `Sparrow` наследява `FlyingBird`, защото може да лети:

```cpp
class Sparrow : public FlyingBird {
public:
    void fly() override {
        std::cout << "Sparrow is flying\n";
    }

    void makeSound() const override {
        std::cout << "Sparrow is making sound...\n";
    }
};

class Eagle : public FlyingBird {
public:
    void fly() override {
        std::cout << "Eagle is flying\n";
    }

    void makeSound() const override {
        std::cout << "Eagle is making sound...\n";
    }
};
```

А `Penguin` наследява само `Bird`, защото е птица, но не е летяща птица:

```cpp
class Penguin : public Bird {
public:
    void makeSound() const override {
        std::cout << "Penguin is making a sound...";
    }
    void swim() {
        std::cout << "Penguin is swimming\n";
    }
    // ...
};
```

Функцията за летене вече приема само `FlyingBird`:

```cpp
void makeBirdFly(FlyingBird& bird) {
    bird.fly();
}
```

### Използване

```cpp
int main() {
    Sparrow sparrow;
    Penguin penguin;

    makeBirdFly(sparrow); // OK

    // makeBirdFly(penguin); // Няма да се компилира
}
```

Това е по-добре, защото грешката се хваща още при компилация, а не чак по време на изпълнение.

---

## С какво помага?

Liskov Substitution Principle помага кодът да бъде:

- по-логически правилен;
- по-безопасен при наследяване;
- по-лесен за разбиране;
- с по-малко неочаквани runtime грешки;
- по-добре структуриран около реалното поведение на обектите.

---

## Обобщение

Не е достатъчно един клас да звучи като правилен наследник.

Важно е наследникът наистина да може да се използва навсякъде, където се очаква базовият клас.

Така кодът описва реалното поведение по-точно и не се налага да хвърляме грешки за неща, които изобщо не трябва да са позволени.
