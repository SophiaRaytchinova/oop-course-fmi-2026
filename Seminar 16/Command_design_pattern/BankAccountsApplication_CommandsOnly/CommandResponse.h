#pragma once

#include <string>

class CommandResponse {
public:
    explicit CommandResponse(const std::string& message);

    const std::string& getMessage() const;

private:
    std::string message;
};
