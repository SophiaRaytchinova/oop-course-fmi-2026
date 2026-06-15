#include "BankService.h"

BankService::BankService(const std::shared_ptr<AccountRepository>& accountRepository,
                         const std::shared_ptr<TransactionRepository>& transactionRepository)
    : accountRepository(accountRepository),
      transactionRepository(transactionRepository) {}

double BankService::getBalance(const std::string&) const {
    // ... implement logic for retrieving the account balance
    return 0.0;
}

double BankService::deposit(const std::string&, const double&) {
    // ... implement logic for depositing money and recording a transaction
    return 0.0;
}

double BankService::withdraw(const std::string&, const double&) {
    // ... implement logic for withdrawing money and recording a transaction
    return 0.0;
}

double BankService::transfer(const std::string&,
                             const std::string&,
                             const double&) {
    // ... implement logic for transferring money and recording a transaction
    return 0.0;
}
