#pragma once

#include "Command.h"

class HelpCommand final : public Command {
public:
    CommandResponse execute() override;
};
