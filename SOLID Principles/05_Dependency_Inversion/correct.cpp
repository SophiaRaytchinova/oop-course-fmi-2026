#include <iostream>
#include <memory>
#include <string>

class DBConnection {
public:
    virtual ~DBConnection() = default;

    virtual void connect() = 0;
    virtual void saveUser(const std::string& username) = 0;
};

class MySQLConnection : public DBConnection {
public:
    void connect() override {
        std::cout << "Connecting to MySQL...\n";
    }

    void saveUser(const std::string& username) override {
        std::cout << "Saving user to MySQL: " << username << '\n';
    }
};

class PostgreSQLConnection : public DBConnection {
public:
    void connect() override {
        std::cout << "Connecting to PostgreSQL...\n";
    }

    void saveUser(const std::string& username) override {
        std::cout << "Saving user to PostgreSQL: " << username << '\n';
    }
};

class MongoConnection : public DBConnection {
public:
    void connect() override {
        std::cout << "Connecting to MongoDB...\n";
    }

    void saveUser(const std::string& username) override {
        std::cout << "Saving user to MongoDB: " << username << '\n';
    }
};

class UserRepository {
private:
    std::shared_ptr<DBConnection> db;

public:
    explicit UserRepository(const std::shared_ptr<DBConnection>& db)
        : db(db) {
        this->db->connect();
    }

    void save(const std::string& username) {
        db->saveUser(username);
    }
};

int main() {
    std::shared_ptr<DBConnection> mysql =
        std::make_shared<MySQLConnection>();

    UserRepository mysqlUsers(mysql);
    mysqlUsers.save("test");

    std::cout << "----\n";

    std::shared_ptr<DBConnection> postgres =
        std::make_shared<PostgreSQLConnection>();

    UserRepository postgresUsers(postgres);
    postgresUsers.save("abc");

    std::cout << "----\n";

    std::shared_ptr<DBConnection> mongo =
        std::make_shared<MongoConnection>();

    UserRepository mongoUsers(mongo);
    mongoUsers.save("def");
}
