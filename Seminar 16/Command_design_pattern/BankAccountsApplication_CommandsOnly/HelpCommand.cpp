#include "HelpCommand.h"

CommandResponse HelpCommand::execute() {
    return CommandResponse(
        "Available commands:\n"
        "  login <username> <password>\n"
        "  logout\n"
        "  deposit <amount>\n"
        "  withdraw <amount>\n"
        "  transfer <recipient> <amount>\n"
        "  balance\n"
        "  help\n"
        "  exit"
    );
}
