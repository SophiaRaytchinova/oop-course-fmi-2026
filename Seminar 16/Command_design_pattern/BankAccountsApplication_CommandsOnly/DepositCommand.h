#pragma once

#include "AuthenticationContext.h"
#include "BankService.h"
#include "Command.h"

#include <memory>

class DepositCommand final : public Command {
public:
    DepositCommand(const std::shared_ptr<AuthenticationContext>& authenticationContext,
                   const std::shared_ptr<BankService>& bankService,
                   const double& amount);

    CommandResponse execute() override;

private:
    std::shared_ptr<AuthenticationContext> authenticationContext;
    std::shared_ptr<BankService> bankService;
    double amount;
};
