#pragma once

#include "AccountRepository.h"
#include "TransactionRepository.h"

#include <memory>
#include <string>

class BankService {
public:
    BankService(const std::shared_ptr<AccountRepository>& accountRepository,
                const std::shared_ptr<TransactionRepository>& transactionRepository);

    double getBalance(const std::string& username) const;
    double deposit(const std::string& username, const double& amount);
    double withdraw(const std::string& username, const double& amount);
    double transfer(const std::string& sender,
                    const std::string& recipient,
                    const double& amount);

private:
    std::shared_ptr<AccountRepository> accountRepository;
    std::shared_ptr<TransactionRepository> transactionRepository;
};
