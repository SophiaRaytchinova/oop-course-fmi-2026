#include "Transaction.h"

Transaction::Transaction() = default;

Transaction::Transaction(const std::string& type,
                         const std::string& sender,
                         const std::string& recipient,
                         const double& amount)
    : type(type), sender(sender), recipient(recipient), amount(amount) {}

const std::string& Transaction::getType() const {
    return type;
}

const std::string& Transaction::getSender() const {
    return sender;
}

const std::string& Transaction::getRecipient() const {
    return recipient;
}

double Transaction::getAmount() const {
    return amount;
}
