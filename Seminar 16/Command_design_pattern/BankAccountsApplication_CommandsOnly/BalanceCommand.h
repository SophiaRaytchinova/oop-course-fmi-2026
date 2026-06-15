#pragma once

#include "AuthenticationContext.h"
#include "BankService.h"
#include "Command.h"

#include <memory>

class BalanceCommand final : public Command {
public:
    BalanceCommand(const std::shared_ptr<AuthenticationContext>& authenticationContext,
                   const std::shared_ptr<BankService>& bankService);

    CommandResponse execute() override;

private:
    std::shared_ptr<AuthenticationContext> authenticationContext;
    std::shared_ptr<BankService> bankService;
};
