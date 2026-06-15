#pragma once

#include <string>

class Account {
public:
    Account();
    Account(const std::string& ownerUsername, const double& balance);

    const std::string& getOwnerUsername() const;
    double getBalance() const;
    void setBalance(const double& balance);

private:
    std::string ownerUsername;
    double balance = 0.0;
};
