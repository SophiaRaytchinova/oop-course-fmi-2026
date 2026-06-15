#include "WithdrawCommand.h"

#include <iomanip>
#include <sstream>

WithdrawCommand::WithdrawCommand(
    const std::shared_ptr<AuthenticationContext>& authenticationContext,
    const std::shared_ptr<BankService>& bankService,
    const double& amount)
    : authenticationContext(authenticationContext),
      bankService(bankService),
      amount(amount) {}

CommandResponse WithdrawCommand::execute() {
    if (!authenticationContext->isAuthenticated()) {
        return CommandResponse("You must be logged in.");
    }

    const std::string& username =
        authenticationContext->getAuthenticatedUser().getUsername();

    const double balance = bankService->withdraw(username, amount);

    std::ostringstream output;
    output << std::fixed << std::setprecision(2)
           << "Withdrawal completed. Balance: " << balance;

    return CommandResponse(output.str());
}
