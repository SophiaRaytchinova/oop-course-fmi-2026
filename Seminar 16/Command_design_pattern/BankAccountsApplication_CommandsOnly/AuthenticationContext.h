#pragma once

#include "User.h"
#include "UserRepository.h"

#include <memory>
#include <string>

class AuthenticationContext {
public:
    explicit AuthenticationContext(const std::shared_ptr<UserRepository>& userRepository);

    bool login(const std::string& username, const std::string& password);
    void logout();

    bool isAuthenticated() const;
    const User& getAuthenticatedUser() const;

private:
    std::shared_ptr<UserRepository> userRepository;
    std::optional<User> authenticatedUser;
};
