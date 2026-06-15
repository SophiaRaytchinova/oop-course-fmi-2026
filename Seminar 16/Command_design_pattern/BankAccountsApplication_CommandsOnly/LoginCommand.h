#pragma once

#include "AuthenticationContext.h"
#include "Command.h"

#include <memory>
#include <string>

class LoginCommand final : public Command {
public:
    LoginCommand(const std::shared_ptr<AuthenticationContext>& authenticationContext,
                 const std::string& username,
                 const std::string& password);

    CommandResponse execute() override;

private:
    std::shared_ptr<AuthenticationContext> authenticationContext;
    std::string username;
    std::string password;
};
