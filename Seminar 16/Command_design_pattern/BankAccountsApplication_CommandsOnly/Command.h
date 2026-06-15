#pragma once

#include "CommandResponse.h"

class Command {
public:
    virtual ~Command() = default;
    virtual CommandResponse execute() = 0;
};
