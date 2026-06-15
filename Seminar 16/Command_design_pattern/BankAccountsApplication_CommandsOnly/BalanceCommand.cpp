#include "BalanceCommand.h"

#include <iomanip>
#include <sstream>

BalanceCommand::BalanceCommand(
    const std::shared_ptr<AuthenticationContext>& authenticationContext,
    const std::shared_ptr<BankService>& bankService)
    : authenticationContext(authenticationContext), bankService(bankService) {}

CommandResponse BalanceCommand::execute() {
    if (!authenticationContext->isAuthenticated()) {
        return CommandResponse("You must be logged in.");
    }

    const std::string& username = authenticationContext->getAuthenticatedUser().getUsername();

    const double balance = bankService->getBalance(username);

    std::ostringstream output;
    output << std::fixed << std::setprecision(2)
           << "Balance: " << balance;

    return CommandResponse(output.str());
}
