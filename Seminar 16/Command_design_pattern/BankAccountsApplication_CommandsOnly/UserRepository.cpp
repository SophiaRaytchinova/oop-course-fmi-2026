#include "UserRepository.h"

UserRepository::UserRepository(const std::string& filePath)
    : filePath(filePath) {}

void UserRepository::load() {
    // ... implement logic for loading users from file
}

void UserRepository::save() const {
    // ... implement logic for saving users to file
}

std::optional<User> UserRepository::findByCredentials(const std::string&,
                                                        const std::string&) const {
    // ... implement logic for finding a user by username and password
    return std::nullopt;
}

// ...
