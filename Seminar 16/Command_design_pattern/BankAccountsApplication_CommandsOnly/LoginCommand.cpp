#include "LoginCommand.h"

LoginCommand::LoginCommand(
    const std::shared_ptr<AuthenticationContext>& authenticationContext,
    const std::string& username,
    const std::string& password)
    : authenticationContext(authenticationContext), username(username), password(password) {}

CommandResponse LoginCommand::execute() {
    if (!authenticationContext->login(username, password)) {
        return CommandResponse("Login failed.");
    }

    return CommandResponse("Logged in as " + username + ".");
}
