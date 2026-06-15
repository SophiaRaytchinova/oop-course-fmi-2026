#include "Account.h"

Account::Account() = default;

Account::Account(const std::string& ownerUsername, const double& balance)
    : ownerUsername(ownerUsername), balance(balance) {}

const std::string& Account::getOwnerUsername() const {
    return ownerUsername;
}

double Account::getBalance() const {
    return balance;
}

void Account::setBalance(const double& balance) {
    this->balance = balance;
}
