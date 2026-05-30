#include <iostream>
#include <string>
#include <memory>

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

// what if we want to change to another database?
// We would have to change the UserRepository class
// which violates Dependency Inversion Principle
    std::shared_ptr<MySQLConnection> db;

public:
    UserRepository(const std::shared_ptr<MySQLConnection>& db) : db(db) {
        db->connect();
    }

    void save(const std::string& username) {
        db->saveUser(username);
    }
};

int main() {
    UserRepository userRepository;
    userRepository.save("test");
    userRepository.save("abc");
}
