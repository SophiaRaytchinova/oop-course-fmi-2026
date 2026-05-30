# Dependency Inversion Principle

> Класовете с по-важна бизнес логика не трябва да зависят директно от конкретни low-level класове. Те трябва да зависят от абстракции.

- Компонентите от високо ниво на абстракция не трябва да зависят от компоненти на ниско ниво на абстракция

С други думи: `UserRepository` не трябва да бъде вързан директно за `MySQL`, `PostgreSQL` или `MongoDB`.

По-добре е да зависи от общ интерфейс, например `DBConnection`, а конкретната база да бъде подадена отвън.

---

## Проблемът

Нека имаме `UserRepository`, който записва потребители в база данни.

Лошият вариант е `UserRepository` да създава или използва директно конкретна база, например `MySQLConnection`:

```cpp
class MySQLConnection {
public:
    void connect() {
        std::cout << "Connecting to MySQL...\n";
    }

    void saveUser(const std::string& username) {
        std::cout << "Saving user to MySQL: " << username << '\n';
    }
};

class UserRepository {
private:
    std::shared_ptr<MySQLConnection> db;

public:
    UserRepository(const std::shared_ptr<MySQLConnection>& db) : db(db) {
        db->connect();
    }

    void save(const std::string& username) {
        db->saveUser(username);
    }
};
```

### Какъв е проблемът?

`UserRepository` вече зависи директно от `MySQLConnection`.

Това означава, че ако утре искаме да използваме `PostgreSQLConnection` или `MongoDBConnection`, трябва да променяме самия `UserRepository`.

Тоест класът, който се грижи за потребителите, знае твърде много за конкретната база данни.

Това прави кода:

- по-труден за промяна
- по-труден за тестване
- по-силно вързан към конкретна технология
- по-малко гъвкав при смяна на базата

---

## По-добро решение

Вместо `UserRepository` да зависи от конкретна база, правим абстракция:

```cpp
class DBConnection {
public:
    virtual ~DBConnection() = default;

    virtual void saveUser(const std::string& username) = 0;
};
```

След това конкретните видове имплементират този интерфейс:

```cpp
class MySQLConnection : public DBConnection {
public:
    void saveUser(const std::string& username) override {
        std::cout << "Saving user to MySQL: " << username << std::endl;
    }
};

class PostgreSQLConnection : public DBConnection {
public:
    void saveUser(const std::string& username) override {
        std::cout << "Saving user to PostgreSQL: " << username << std::endl;
    }
};

class MongoConnection : public DBConnection {
public:
    void saveUser(const std::string& username) override {
        std::cout << "Saving user to MongoDB: " << username << std::endl;
    }
};
```

Сега `UserRepository` не зависи от конкретна база данни.

Той държи указател към абстракцията `DBConnection`:

```cpp
class UserRepository {
private:
    std::shared_ptr<DBConnection> db;

public:
    UserRepository(std::shared_ptr<DBConnection> db)
        : db(db) {}

    void save(const std::string& username) {
        db->saveUser(username);
    }
};
```

Това е dependency injection: подаваме зависимостта отвън, вместо `UserRepository` сам да си я създава.

---

Можем да използваме MySQL:

```cpp
auto db = std::make_shared<MySQLConnection>();
UserRepository users(db);

users.save("test");
```

Или PostgreSQL:

```cpp
auto db = std::make_shared<PostgreSQLConnection>();
UserRepository users(db);

users.save("abc");
```

Или MongoDB:

```cpp
auto db = std::make_shared<MongoConnection>();
UserRepository users(db);

users.save("def");
```

`UserRepository` не се променя.

Променя се само конкретната имплементация, която му подаваме.

---

## Защо това е по-добре?

Когато зависим от абстракция:

- можем лесно да сменим класа, без да променяме класа, който го използва
- можем лесно да добавим нова база
- бизнес логиката не е вързана към конкретна технология
- кодът става по-гъвкав и по-лесен за поддръжка
