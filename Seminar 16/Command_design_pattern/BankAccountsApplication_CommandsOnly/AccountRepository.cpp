#include "AccountRepository.h"

AccountRepository::AccountRepository(const std::string& filePath)
    : filePath(filePath) {}

void AccountRepository::load() {
    // ... implement logic for loading accounts from filePath
}

void AccountRepository::save() const {
    // ... implement logic for saving accounts to filePath
}

std::optional<Account> AccountRepository::findByUsername(const std::string&) const {
    // ... implement logic for finding an account by username
    return std::nullopt;
}
