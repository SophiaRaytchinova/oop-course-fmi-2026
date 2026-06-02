#pragma once
#include <vector>
#include <memory>
#include <optional>
#include <string>
#include <memory>
#include "Resume.h"

class Requirement {
public:
    virtual std::optional<std::string> check(const Resume& resume) const = 0;
    virtual std::unique_ptr<Requirement> clone() const = 0;
    virtual ~Requirement() = default;
};
