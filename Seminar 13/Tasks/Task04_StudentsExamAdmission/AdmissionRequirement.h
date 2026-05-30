#pragma once
#include <memory>
#include <optional>
#include "Student.h"

class AdmissionRequirement {
public:
    // if the optional contains a message, then the check did not pass
    // if the optional is empty (std::nullopt), then the check passed
    virtual std::optional<std::string> check(const Student& student) const = 0;

    virtual std::unique_ptr<AdmissionRequirement> clone() const = 0;
    virtual ~AdmissionRequirement() = default;
};
