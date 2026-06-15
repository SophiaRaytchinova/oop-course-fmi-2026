#pragma once

#include "AuthenticationContext.h"
#include "BankService.h"
#include "Command.h"

#include <memory>
#include <string>
#include <vector>

class CommandFactory {
public:
    CommandFactory(const std::shared_ptr<AuthenticationContext>& authenticationContext,
                   const std::shared_ptr<BankService>& bankService);

    std::unique_ptr<Command> create(const std::string& input) const;

private:
    static std::vector<std::string> tokenize(const std::string& input);

    std::shared_ptr<AuthenticationContext> authenticationContext;
    std::shared_ptr<BankService> bankService;
};
