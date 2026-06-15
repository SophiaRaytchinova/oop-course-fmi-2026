#include "AuthenticationContext.h"

#include <stdexcept>

AuthenticationContext::AuthenticationContext(
    const std::shared_ptr<UserRepository>& userRepository)
    : userRepository(userRepository) {}

bool AuthenticationContext::login(const std::string& username, const std::string& password) {
    if (isAuthenticated()) {
        return false;
    }

    authenticatedUser = userRepository->findByCredentials(username, password);
    return authenticatedUser != std::nullopt;
}

void AuthenticationContext::logout() {
    authenticatedUser.reset();

    // ... implement additional logout logic if needed
}

bool AuthenticationContext::isAuthenticated() const {
    return authenticatedUser != std::nullopt;
}

const User& AuthenticationContext::getAuthenticatedUser() const {
    if (!isAuthenticated()) {
        throw std::runtime_error("No user is currently logged in.");
    }

    return *authenticatedUser;
}
