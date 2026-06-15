#include "DepositCommand.h"

#include <iomanip>
#include <sstream>

DepositCommand::DepositCommand(
    const std::shared_ptr<AuthenticationContext>& authenticationContext,
    const std::shared_ptr<BankService>& bankService,
    const double& amount)
    : authenticationContext(authenticationContext), bankService(bankService), amount(amount) {}

CommandResponse DepositCommand::execute() {
    if (!authenticationContext->isAuthenticated()) {
        return CommandResponse("You must be logged in.");
    }

    const std::string& username = authenticationContext->getAuthenticatedUser().getUsername();

    const double balance = bankService->deposit(username, amount);

    std::ostringstream output;
    output << std::fixed << std::setprecision(2)
           << "Deposit completed. Balance: " << balance;

    return CommandResponse(output.str());
}
