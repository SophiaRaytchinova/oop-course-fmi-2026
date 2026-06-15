#pragma once

#include "Account.h"

#include <string>
#include <vector>
#include <optional>

class AccountRepository {
public:
    explicit AccountRepository(const std::string& filePath);

    void load();
    void save() const;

    std::optional<Account> findByUsername(const std::string& username) const;

private:
    std::string filePath;
    std::vector<Account> accounts;
};
