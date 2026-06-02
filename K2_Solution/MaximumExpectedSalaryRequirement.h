#pragma once
#include "Requirement.h"

class MaximumExpectedSalaryRequirement : public Requirement {
public:
    explicit MaximumExpectedSalaryRequirement(double maxExpectedSalary);
    std::optional<std::string> check(const Resume& resume) const override;
    std::unique_ptr<Requirement> clone() const override;
private:
    double maxExpectedSalary;
};
