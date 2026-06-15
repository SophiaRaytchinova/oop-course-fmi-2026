#include "CommandFactory.h"

#include "BalanceCommand.h"
#include "DepositCommand.h"
#include "HelpCommand.h"
#include "LoginCommand.h"
#include "LogoutCommand.h"
#include "TransferCommand.h"
#include "WithdrawCommand.h"

#include <sstream>
#include <stdexcept>

CommandFactory::CommandFactory(
    const std::shared_ptr<AuthenticationContext>& authenticationContext,
    const std::shared_ptr<BankService>& bankService)
    : authenticationContext(authenticationContext),
      bankService(bankService) {}

std::unique_ptr<Command> CommandFactory::create(const std::string& input) const {
    const std::vector<std::string> tokens = tokenize(input);
    if (tokens.empty()) {
        throw std::invalid_argument("Command cannot be empty.");
    }

    const std::string& commandName = tokens[0];

    if (commandName == "login") {
        return std::make_unique<LoginCommand>(authenticationContext, tokens[1], tokens[2]);
    }

    if (commandName == "logout") {
        return std::make_unique<LogoutCommand>(authenticationContext);
    }

    if (commandName == "deposit") {
        return std::make_unique<DepositCommand>(authenticationContext, bankService, std::stod(tokens[1]));
    }

    if (commandName == "withdraw") {
        return std::make_unique<WithdrawCommand>(authenticationContext, bankService, std::stod(tokens[1]));
    }

    if (commandName == "transfer") {
        return std::make_unique<TransferCommand>(authenticationContext, bankService, tokens[1], std::stod(tokens[2]));
    }

    if (commandName == "balance") {
        return std::make_unique<BalanceCommand>(authenticationContext, bankService);
    }

    if (commandName == "help") {
        return std::make_unique<HelpCommand>();
    }

    throw std::invalid_argument("Unknown command: " + commandName);
}

std::vector<std::string> CommandFactory::tokenize(const std::string& input) {
    std::istringstream stream(input);
    std::vector<std::string> tokens;
    std::string token;

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

