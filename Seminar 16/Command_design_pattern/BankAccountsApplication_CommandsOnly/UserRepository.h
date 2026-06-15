#pragma once

#include "User.h"

#include <optional>
#include <string>
#include <vector>

class UserRepository {
public:
    explicit UserRepository(const std::string& filePath);

    void load();
    void save() const;

    std::optional<User> findByCredentials(const std::string& username,
                                            const std::string& password) const;

    // ...
private:
    std::string filePath;
    std::vector<User> users;
};
