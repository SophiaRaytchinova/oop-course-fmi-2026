#include "LogoutCommand.h"

LogoutCommand::LogoutCommand(
    const std::shared_ptr<AuthenticationContext>& authenticationContext)
    : authenticationContext(authenticationContext) {}

CommandResponse LogoutCommand::execute() {
    if (!authenticationContext->isAuthenticated()) {
        return CommandResponse("No user is currently logged in.");
    }

    authenticationContext->logout();
    return CommandResponse("Logged out.");
}
