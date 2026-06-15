#include "TransferCommand.h"

#include <iomanip>
#include <sstream>

TransferCommand::TransferCommand(
    const std::shared_ptr<AuthenticationContext>& authenticationContext,
    const std::shared_ptr<BankService>& bankService,
    const std::string& recipient,
    const double& amount)
    : authenticationContext(authenticationContext),
      bankService(bankService),
      recipient(recipient),
      amount(amount) {}

CommandResponse TransferCommand::execute() {
    if (!authenticationContext->isAuthenticated()) {
        return CommandResponse("You must be logged in.");
    }

    const std::string& sender =
        authenticationContext->getAuthenticatedUser().getUsername();

    const double balance = bankService->transfer(sender, recipient, amount);

    std::ostringstream output;
    output << std::fixed << std::setprecision(2)
           << "Transfer completed. Balance: " << balance;

    return CommandResponse(output.str());
}
