#pragma once

#include "Transaction.h"

#include <string>
#include <vector>

class TransactionRepository {
public:
    explicit TransactionRepository(const std::string& filePath);

    void load();
    void save() const;
    void add(const Transaction& transaction);
    // ...

private:
    std::string filePath;
    std::vector<Transaction> transactions;
};
