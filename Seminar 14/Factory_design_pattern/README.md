# Factory Design Pattern. Factory Method. Abstract Factory.

### ℹ️ [Factory Method - допълнителна информация](https://refactoring.guru/design-patterns/factory-method)

### ℹ️ [Abstract Factory - допълнителна информация](https://refactoring.guru/design-patterns/abstract-factory)

---

**Factory** е creational design pattern, който се използва, когато искаме да отделим логиката за **създаване на обекти** от кода, който ги използва.

Най-просто казано, вместо навсякъде в програмата да пишем:

```cpp
new SomeClass();
```

или директно да създаваме конкретни класове:

```cpp
EmailNotification notification;
```

използваме отделна функция или клас, който отговаря за създаването на правилния обект.

Тоест идеята е:

> Кодът, който използва обекта, не трябва задължително да знае точно кой конкретен клас се създава.

---

Factory pattern се използва, когато имаме няколко различни класа, които имат общ интерфейс или базов клас, и искаме да създаваме правилния обект според дадено условие.

Например може да имаме различни видове notification-и:

* `EmailNotification`
* `SmsNotification`
* `PushNotification`

Всички те могат да наследяват общ интерфейс:

```cpp
class Notification {
public:
    virtual void send(const std::string& message) = 0;
    virtual ~Notification() = default;
};
```

Тогава вместо навсякъде в кода да проверяваме какъв тип notification трябва да създадем, можем да изнесем тази логика във factory.

---

### Какъв проблем решава Factory?

Factory решава проблеми от типа:

* „Не искам кодът ми да зависи директно от конкретни класове/наследници“
* „Искам създаването на обекти да е централизирано“
* „Имам няколко класа с общ интерфейс и трябва да избирам кой да създам“
* „Не искам навсякъде да имам `if` / `switch` логика за създаване на обекти“
* „Искам по-лесно да добавям нови типове обекти“

Без factory често се стига до повтаряне на код от този тип:

```cpp
Notification* notification = nullptr;

if (type == "email") {
    notification = new EmailNotification();
} else if (type == "sms") {
    notification = new SmsNotification();
} else if (type == "push") {
    notification = new PushNotification();
}
```

Проблемът е, че ако такава логика се появи на много места, кодът става труден за поддръжка.

Ако решим да добавим нов тип notification, например:

```cpp
SlackNotification
```

ще трябва да търсим всички места в програмата, където има такава логика, и да ги променяме.

Factory pattern решава това, като събира логиката за създаване на обекти на едно място.

---

## Най-разпространеният вариант: Simple Factory

Когато в практиката някой каже просто **factory**, много често има предвид точно **Simple Factory**.

Това е най-лесният и най-често срещаният вариант.

Идеята е много проста:

* имаме отделен factory клас или функция
* подаваме тип, enum или някакъв параметър
* factory-то връща обект от правилния конкретен клас

---

#### Пример:

Имаме общ интерфейс:

```cpp
class Notification {
public:
    virtual void send(const std::string& message) = 0;
    virtual ~Notification() = default;
};
```

Имаме няколко конкретни класа:

```cpp
class EmailNotification : public Notification {
public:
    void send(const std::string& message) override {
        std::cout << "Sending email: " << message << std::endl;
    }
};

class SmsNotification : public Notification {
public:
    void send(const std::string& message) override {
        std::cout << "Sending SMS: " << message << std::endl;
    }
};

class PushNotification : public Notification {
public:
    void send(const std::string& message) override {
        std::cout << "Sending push notification: " << message << std::endl;
    }
};
```

Можем да имаме enum, който описва какъв тип notification искаме:

```cpp
enum class NotificationType {
    Email,
    Sms,
    Push
};
```

След това създаваме factory class:

```cpp
class NotificationFactory {
public:
    static std::unique_ptr<Notification> create(NotificationType type) {
        switch (type) {
            case NotificationType::Email:
                return std::make_unique<EmailNotification>();

            case NotificationType::Sms:
                return std::make_unique<SmsNotification>();

            case NotificationType::Push:
                return std::make_unique<PushNotification>();

            default:
                throw std::invalid_argument("Unknown notification type");
        }
    }
};
```

Използването вече изглежда така:

```cpp
auto notification = NotificationFactory::create(NotificationType::Email);

notification->send("Hello!");
```

Кодът, който използва notification-а, не се интересува дали това е `EmailNotification`, `SmsNotification` или `PushNotification`.

Той работи само с общия интерфейс:

```cpp
Notification
```

---

Вместо да пишем това навсякъде:

```cpp
if (type == NotificationType::Email) {
    // create email notification
} else if (type == NotificationType::Sms) {
    // create sms notification
}
```

имаме едно централизирано място:

```cpp
NotificationFactory::create(type);
```

Така ако се промени логиката за създаване на обектите, променяме само factory-то.

---

### Кога Simple Factory е добра идея?

Simple Factory е добра идея, когато:

* имаме няколко класа с общ интерфейс
* искаме да скрием конкретните класове от клиентския код
* искаме създаването на обекти да бъде централизирано
* обектът, който трябва да се създаде, зависи от входен параметър
* не искаме навсякъде да имаме една и съща `switch` или `if` логика

---

Да кажем, че имаме приложение, което работи с различни типове документи:

* PDF
* Word
* Text

Можем да имаме общ интерфейс:

```cpp
class Document {
public:
    virtual void open() = 0;
    //...
    virtual ~Document() = default;
};
```

Конкретни документи:

```cpp
class PdfDocument : public Document {
public:
    void open() override {
        std::cout << "Opening PDF document" << std::endl;
    }
    //...
};

class WordDocument : public Document {
public:
    void open() override {
        std::cout << "Opening Word document" << std::endl;
    }
    //...
};

class TextDocument : public Document {
public:
    void open() override {
        std::cout << "Opening text document" << std::endl;
    }
    //...
};
```

Factory:

```cpp
enum class DocumentType {
    Pdf,
    Word,
    Text
};

class DocumentFactory {
public:
    static std::unique_ptr<Document> create(DocumentType type) {
        switch (type) {
            case DocumentType::Pdf:
                return std::make_unique<PdfDocument>();

            case DocumentType::Word:
                return std::make_unique<WordDocument>();

            case DocumentType::Text:
                return std::make_unique<TextDocument>();

            default:
                throw std::invalid_argument("Unknown document type");
        }
    }
};
```

Използване:

```cpp
auto document = DocumentFactory::create(DocumentType::Pdf);

document->open();
```

Това е типичният най-разпространен factory подход.

---

## Factory Method

**Factory Method** е малко по-структуриран вариант на factory pattern.

При него не просто имаме един отделен factory class със статичен метод, а имаме метод, който е отговорен за създаването на обект, като наследниците могат да решат какъв конкретен обект да върнат.

Най-често идеята е:

> Базов клас дефинира factory метод, а наследниците решават кой конкретен клас да бъде създаден.

---

#### Пример:

Да кажем, че имаме различни видове транспорт.

Общ интерфейс:

```cpp
class Transport {
public:
    virtual void deliver() = 0;
    virtual ~Transport() = default;
};
```

Конкретни класове:

```cpp
class Truck : public Transport {
public:
    void deliver() override {
        std::cout << "Delivering by truck" << std::endl;
    }
};

class Ship : public Transport {
public:
    void deliver() override {
        std::cout << "Delivering by ship" << std::endl;
    }
};
```

Сега имаме базов клас `Logistics`, който съдържа factory method:

```cpp
class Logistics {
public:
    virtual std::unique_ptr<Transport> createTransport() = 0;

    void planDelivery() {
        auto transport = createTransport();
        transport->deliver();
    }

    virtual ~Logistics() = default;
};
```

Конкретните наследници решават какъв транспорт да създадат:

```cpp
class RoadLogistics : public Logistics {
public:
    std::unique_ptr<Transport> createTransport() override {
        return std::make_unique<Truck>();
    }
};

class SeaLogistics : public Logistics {
public:
    std::unique_ptr<Transport> createTransport() override {
        return std::make_unique<Ship>();
    }
};
```

Използване:

```cpp
std::unique_ptr<Logistics> logistics = std::make_unique<RoadLogistics>();

logistics->planDelivery();
```

Тук `planDelivery()` не знае дали доставката ще стане с камион или кораб.

Това се решава от конкретния клас:

```cpp
RoadLogistics
SeaLogistics
```

---

### Каква е разликата между Simple Factory и Factory Method?

При **Simple Factory** обикновено имаме нещо такова:

```cpp
NotificationFactory::create(type);
```

Тоест един factory class или функция избира какъв обект да създаде.

При **Factory Method** имаме наследяване:

```cpp
class Logistics {
public:
    virtual std::unique_ptr<Transport> createTransport() = 0;
};
```

И конкретните наследници решават какво да създадат:

```cpp
class RoadLogistics : public Logistics {
public:
    std::unique_ptr<Transport> createTransport() override {
        return std::make_unique<Truck>();
    }
};
```

Най-просто казано:

* **Simple Factory**: изборът често е в `switch` / `if` в отделен factory class
* **Factory Method**: изборът е изнесен в наследниците чрез virtual метод

---

### Кога Factory Method е добра идея?

Factory Method е добра идея, когато:

* имаме базов клас с общ алгоритъм
* част от алгоритъма зависи от това какъв конкретен обект ще се създаде
* искаме наследниците да решават какъв продукт да създадат
* искаме да избегнем твърда зависимост между базовия клас и конкретните продукти

---

## Abstract Factory

**Abstract Factory** се използва, когато искаме да създаваме **семейства от свързани обекти**, без клиентският код да знае конкретните им класове.

Тук вече не създаваме само един тип обект, а група от обекти, които логически вървят заедно.

---

#### Пример:

Да кажем, че правим UI framework.

Имаме различни операционни системи:

* Windows
* macOS

И за всяка от тях имаме различни UI компоненти:

* button
* checkbox

За Windows искаме:

* `WindowsButton`
* `WindowsCheckbox`

За macOS искаме:

* `MacButton`
* `MacCheckbox`

Важно е да не смесваме компонентите.

Не искаме случайно да създадем:

* `WindowsButton`
* `MacCheckbox`

Искаме цялото семейство от обекти да бъде съвместимо.

---

## Пример с Abstract Factory

Общи интерфейси:

```cpp
class Button {
public:
    virtual void render() = 0;
    virtual ~Button() = default;
};

class Checkbox {
public:
    virtual void render() = 0;
    virtual ~Checkbox() = default;
};
```

Windows компоненти:

```cpp
class WindowsButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Windows button" << std::endl;
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Windows checkbox" << std::endl;
    }
};
```

Mac компоненти:

```cpp
class MacButton : public Button {
public:
    void render() override {
        std::cout << "Rendering Mac button" << std::endl;
    }
};

class MacCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Rendering Mac checkbox" << std::endl;
    }
};
```

Сега правим abstract factory интерфейс:

```cpp
class UIFactory {
public:
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;

    virtual ~UIFactory() = default;
};
```

Конкретна factory за Windows:

```cpp
class WindowsFactory : public UIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<WindowsCheckbox>();
    }
};
```

Конкретна factory за macOS:

```cpp
class MacFactory : public UIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<MacCheckbox>();
    }
};
```

Използване:

```cpp
void renderUI(UIFactory& factory) {
    auto button = factory.createButton();
    auto checkbox = factory.createCheckbox();

    button->render();
    checkbox->render();
}
```

Клиентският код не знае дали използва Windows или Mac компоненти.

Той знае само, че има factory, която може да създаде:

```cpp
Button
Checkbox
```

Изборът на конкретнo factory може да стане някъде в началото на програмата:

```cpp
std::unique_ptr<UIFactory> factory;

if (os == "windows") {
    factory = std::make_unique<WindowsFactory>();
} else if (os == "mac") {
    factory = std::make_unique<MacFactory>();
}

renderUI(*factory);
```

---

### Каква е идеята на Abstract Factory?

Идеята е да гарантираме, че създадените обекти са от едно и също семейство.

Например:

```cpp
WindowsFactory
```

създава само Windows компоненти:

```cpp
WindowsButton
WindowsCheckbox
```

А:

```cpp
MacFactory
```

създава само Mac компоненти:

```cpp
MacButton
MacCheckbox
```

Така избягваме смесване на несъвместими обекти.

---

### Сравнение между трите варианта

#### 1. Simple Factory

Използваме, когато искаме просто централизирано създаване на един тип обекти.

Пример:

```cpp
NotificationFactory::create(NotificationType::Email);
```

Подходящо е, когато имаме няколко класа с общ интерфейс и искаме да изберем кой да се създаде според параметър.

Това е най-често срещаният вариант в реалния код, когато хората казват просто „factory“.

---

#### 2. Factory Method

Използваме, когато искаме наследниците на даден базов клас да решават какъв обект да бъде създаден.

Пример:

```cpp
class Logistics {
public:
    virtual std::unique_ptr<Transport> createTransport() = 0;
};
```

Подходящо е, когато имаме общ алгоритъм в базов клас, но конкретният продукт зависи от наследника.

---

#### 3. Abstract Factory

Използваме, когато искаме да създаваме семейства от свързани обекти.

Пример:

```cpp
factory.createButton();
factory.createCheckbox();
```

Подходящо е, когато имаме няколко продукта, които трябва да бъдат съвместими един с друг.

---

### Предимства

#### 1. По-слаба зависимост от конкретни класове

Кодът работи с интерфейси или базови класове, вместо директно с конкретни класове.

Вместо:

```cpp
EmailNotification notification;
```

имаме:

```cpp
std::unique_ptr<Notification> notification;
```

Това прави кода по-гъвкав.

---

#### 2. Централизирано създаване на обекти

Логиката за създаване е на едно място.

Ако трябва да се промени начинът, по който се създават обектите, не обикаляме цялата програма.

---

#### 3. По-лесно добавяне на нови типове

Ако добавим нов клас, например:

```cpp
SlackNotification
```

можем да променим factory-то, без да променяме всички места, които използват notification-и.

---

#### 4. По-чист клиентски код

Кодът, който използва обектите, става по-кратък и по-ясен.

Вместо да съдържа логика за създаване, той просто казва:

```cpp
auto notification = NotificationFactory::create(type);
```

---

### Недостатъци

#### 1. Повече код

Factory pattern обикновено изисква допълнителни класове или функции.

За малки и прости случаи това може да е излишно.

---

#### 2. Може да скрие прекалено много логика

Понякога factory-то става твърде голямо и започва да съдържа много условия:

```cpp
switch (type) {
    case A:
    case B:
    case C:
    case D:
    case E:
    ...
}
```

Тогава може да се наложи по-добра структура или друг pattern.

---

#### 3. Не винаги премахва нуждата от промени

При Simple Factory, ако добавим нов тип, пак трябва да променим factory-то.

Тоест добавяме нов клас, но също така трябва да добавим нов `case` в `switch`.

---

#### 4. Може да е overengineering

Ако имаме само един прост клас, няма нужда да правим factory.

Например това:

```cpp
Point p(3, 4);
```

е напълно нормално.

Няма нужда да го превръщаме в:

```cpp
PointFactory::create(3, 4);
```

освен ако няма специална причина.

---

### Кога е добра идея да използваме Factory?

Factory е разумен избор, когато:

* имаме няколко конкретни класа с общ интерфейс
* клиентският код не трябва да знае точния concrete class
* искаме да централизиране създаването на обекти
* типът на обекта зависи от входни данни
* искаме по-чист и по-гъвкав код
* имаме нужда от polymorphism
* имаме семейства от свързани обекти

Примери за добра употреба:

* notification-и
* payment methods
* file parsers
* document readers
* UI компоненти
* game objects
* database connectors
* serializers и deserializers
* shape objects в graphics приложение

---

### Кога не е добра идея?

Не е нужно да използваме factory, когато:

* класът е прост
* няма различни конкретни варианти
* няма нужда от polymorphism
* няма сложна логика при създаване
* директният constructor е по-ясен

Например:

```cpp
User user("Ivan", 25);
```

Това е достатъчно ясно.

Factory тук може само да усложни кода:

```cpp
UserFactory::create("Ivan", 25);
```

Ако factory-то не добавя реална стойност, по-добре да не се използва.

---

### Factory не е просто заместител на constructor

Factory pattern не означава просто да скрием всеки constructor зад метод `create()`.

Идеята е да имаме смислена причина:

* избор между няколко типа наследници / конкретни класове
* централизирана логика за създаване
* скриване на сложна конструкция
* връщане на обект през интерфейс
* гарантиране, че свързани обекти се създават заедно

Ако няма такава причина, обикновеният constructor често е по-доброто решение.

---