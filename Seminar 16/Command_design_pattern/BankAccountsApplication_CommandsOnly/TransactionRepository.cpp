#include "TransactionRepository.h"

TransactionRepository::TransactionRepository(const std::string& filePath)
    : filePath(filePath) {}

void TransactionRepository::load() {
    // ... implement logic for loading transactions from text file
}

void TransactionRepository::save() const {
    // ... implement logic for saving transactions to text file
}

void TransactionRepository::add(const Transaction& t) {
    // ... implement logic for adding a transaction to the vector
    // perform validation or other business logic
    transactions.push_back(t);
    // ...
}
