#pragma once

#include <string>

class Transaction {
public:
    Transaction();
    Transaction(const std::string& type,
                const std::string& sender,
                const std::string& recipient,
                const double& amount);

    const std::string& getType() const;
    const std::string& getSender() const;
    const std::string& getRecipient() const;
    double getAmount() const;

private:
    std::string type;
    std::string sender;
    std::string recipient;
    double amount = 0.0;
};
