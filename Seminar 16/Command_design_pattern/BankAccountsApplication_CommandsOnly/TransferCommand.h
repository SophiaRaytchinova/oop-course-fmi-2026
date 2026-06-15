#pragma once

#include "AuthenticationContext.h"
#include "BankService.h"
#include "Command.h"

#include <memory>
#include <string>

class TransferCommand final : public Command {
public:
    TransferCommand(const std::shared_ptr<AuthenticationContext>& authenticationContext,
                    const std::shared_ptr<BankService>& bankService,
                    const std::string& recipient,
                    const double& amount);

    CommandResponse execute() override;

private:
    std::shared_ptr<AuthenticationContext> authenticationContext;
    std::shared_ptr<BankService> bankService;
    std::string recipient;
    double amount;
};
