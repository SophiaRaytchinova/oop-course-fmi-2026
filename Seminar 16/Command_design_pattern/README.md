# Command Design Pattern

**Command** е поведенчески (behavioral) design pattern, при който дадено действие се представя като самостоятелен обект.

В контекста на конзолно приложение потребителят може да въвежда команди като:

```text
login alice password123
deposit 500
withdraw 100
transfer bob 50
logout
```

Вместо цялата логика за разпознаване и изпълнение на тези операции да бъде събрана в голям `if/else` или `switch`, всяко действие се представя чрез отделен command клас:

```text
LoginCommand
DepositCommand
WithdrawCommand
TransferCommand
LogoutCommand
```

Всички команди споделят общ интерфейс и могат да бъдат изпълнявани по един и същ начин.

---

## Основен проблем

Без Command pattern главният цикъл на приложението лесно може да започне да изглежда така:

```cpp
if (commandName == "deposit") {
    // parse arguments
    // validate input
    // execute deposit logic
} else if (commandName == "withdraw") {
    // parse arguments
    // validate input
    // execute withdraw logic
} else if (commandName == "transfer") {
    // parse arguments
    // validate input
    // execute transfer logic
}
```

С добавянето на нови операции този код:

- става все по-голям;
- смесва разпознаване на входа с изпълнение на действията;
- зависи от всички компоненти с бизнес логика;
- трудно се разширява и тества;
- изисква промяна на централния код при всяка нова команда.

Command pattern разделя тези отговорности.

---

## Основна структура

Общият интерфейс може да бъде съвсем малък:

```cpp
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};
```
>Не е нужно методът `execute()` да връща `void`. Може да връща и някакъв обект, който да съдържа информация за извършената от командата логика, например `CommandResponse`.

Всяка конкретна команда:

- пази аргументите, подадени от потребителя
- пази нужните зависимости
- имплементира `execute()`
- делегира реалната работа към подходящите компоненти на приложението

Пример:

```cpp
class WithdrawCommand final : public Command {
public:
    WithdrawCommand(
        const std::shared_ptr<BankService>&bankService,
        double amount
    )
        : BankService(bankService),
          amount(amount) {}

    void execute() override {
        bankService->withdraw(amount);
    }

private:
    std::shared_ptr<BankService> bankService;
    double amount;
};
```

`WithdrawCommand` не е самата банкова система и не трябва да съдържа цялата логика за теглене.

Той представя потребителското намерение:

```text
withdraw 100
```

и делегира изпълнението към компонента, който отговаря за съответната логика.

Същият подход може да се използва за останалите операции:

```cpp
DepositCommand
TransferCommand
LoginCommand
LogoutCommand
```

---

## CommandFactory

`CommandFactory` отговаря за създаването на правилния command обект според въведения текст.


Опростен интерфейс:

```cpp
class CommandFactory {
public:
    CommandFactory(
        const std::shared_ptr<BankService>&bankService,
        const std::shared_ptr<AuthenticationContext>&authenticationContext
    );

    std::unique_ptr<Command> create(
        const std::string& input
    ) const;

private:
    std::shared_ptr<BankService> bankService;
    std::shared_ptr<AuthenticationContext> authenticationContext;
};
```

Factory-то може да:

1. раздели входа на име на команда и аргументи
2. извършва проверки/валидации ако са нужни
2. преобразува аргументите до нужните типове
4. създава конкретния command
5. подава нужните зависимости чрез конструктора

Примерна идея:

```cpp
std::unique_ptr<Command> CommandFactory::create(
    const std::string& input
) const {
    const auto tokens = split(input);

    if (tokens.empty()) {
        throw std::invalid_argument("Empty command");
    }

    if (tokens[0] == "withdraw") {
        const double amount = std::stod(tokens.at(1));

        return std::make_unique<WithdrawCommand>(
            bankService,
            amount
        );
    }

    if (tokens[0] == "deposit") {
        const double amount = std::stod(tokens.at(1));

        return std::make_unique<DepositCommand>(
            bankService,
            amount
        );
    }

    throw std::invalid_argument("Unknown command");
}
```

Това е опростен пример. Целта му е да покаже ролята на factory-то, а не да представи пълна имплементация на parsing и validation.

---

## Изпълнение на команда

Главният цикъл на приложението остава малък:

```cpp
while (true) {
    std::string input;
    std::getline(std::cin, input);

    auto command = commandFactory.create(input);
    command->execute();
}
```

Този код не трябва да знае:

- как се извършва тегленето;
- как се извършва трансферът;
- как работи login;
- от кои компоненти зависи всяка операция;
- колко аргумента има конкретната команда.

Той работи единствено с общия интерфейс:

```cpp
Command
```

---

## Делегиране към други компоненти

Command класовете не трябва да се превръщат в място, в което се събира цялата бизнес логика.

Тяхната основна роля е да:

- представят конкретно действие;
- пазят аргументите на действието;
- използват нужните зависимости;
- стартират правилната операция.

Например:

```cpp
void TransferCommand::execute() {
    bankService_->transfer(
        recipient_,
        amount_
    );
}
```

Самият `BankService` може да отговаря за:

- проверка на наличност
- намиране на сметки
- промяна на баланс
- записване на транзакция
- прилагане на бизнес правила

По същия начин:

```cpp
LoginCommand
```

може да делегира към:

```cpp
AuthenticationContext
```

Така command класовете остават малки и ясно фокусирани.


---

```text
"withdraw 100"
        ↓
CommandFactory
        ↓
WithdrawCommand
        ↓
execute()
        ↓
BankService
```

## Влияние върху дизайна на класовете

Command pattern води до ясно разделение между:

### Разпознаване на командата

Извършва се от:

```cpp
CommandFactory
```

### Представяне на действието

Извършва се от:

```cpp
DepositCommand
WithdrawCommand
TransferCommand
```

### Реална application и business логика

Извършва се от компоненти като:

```cpp
BankService
AuthenticationContext
```

### Стартиране на действието

Извършва се чрез общия интерфейс:

```cpp
command->execute();
```

Това намалява директните зависимости между конзолния интерфейс и конкретната логика на приложението.

---

## Основни предимства

### По-малко coupling

Главният цикъл зависи само от `Command`, а не от всички конкретни операции и service класове.

### По-лесно добавяне на нови команди

За нова операция може да се добави нов клас без да се променя начинът, по който командите се изпълняват.

```cpp
class ChangePasswordCommand : public Command {
    // ...
};
```


### По-добро разделение на отговорностите

- Factory-то създава команди
- Командите представят действия
- Сървисите съдържат нужната логика
- Конзолното приложение чете вход и изпълнява команди

### Ясно представяне на операциите

Класове като:

```text
LoginCommand
WithdrawCommand
TransferCommand
```

показват директно какви действия поддържа приложението.

### Възможност за повторна употреба

Една и съща command имплементация може да бъде използвана и от друг интерфейс, стига той да може да създаде и изпълни съответния command.

### Централизирано създаване

`CommandFactory` събира на едно място логиката за избор и създаване на конкретните команди.

---

## Кога е подходящ

Този дизайн е подходящ, когато:

- приложението поддържа много текстови команди
- командите имат различни аргументи
- всяка команда използва различни компоненти
- искаме да отделим конзолния вход от логиката
- искаме нови команди да се добавят сравнително лесно
- искаме общ механизъм за изпълнение

---

## Обобщение

В този пример Command pattern превръща въведените от потребителя действия в обекти:

```text
"deposit 500"    -> DepositCommand
"withdraw 100"   -> WithdrawCommand
"transfer bob 50" -> TransferCommand
```

`CommandFactory` разпознава входа и създава правилния обект.

След това приложението изпълнява всяка команда по един и същ начин:

```cpp
command->execute();
```

Конкретните commands пазят необходимите аргументи и използват компонентите, към които трябва да делегират работата.

Основната полза е, че:

- конзолният интерфейс не зависи от конкретните операции
- всяко действие има собствен клас
- бизнес логиката остава в подходящите компоненти
- приложението става по-лесно за разширяване, поддръжка и тестване
