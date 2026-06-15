#pragma once

#include "AuthenticationContext.h"
#include "Command.h"

#include <memory>

class LogoutCommand final : public Command {
public:
    explicit LogoutCommand(const std::shared_ptr<AuthenticationContext>& authenticationContext);

    CommandResponse execute() override;

private:
    std::shared_ptr<AuthenticationContext> authenticationContext;
};
