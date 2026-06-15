#include "CommandResponse.h"

CommandResponse::CommandResponse(const std::string& message)
    : message(message) {}

const std::string& CommandResponse::getMessage() const {
    return message;
}
