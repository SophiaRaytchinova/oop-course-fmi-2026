#include "MaximumExpectedSalaryRequirement.h"
#include <format>

MaximumExpectedSalaryRequirement::MaximumExpectedSalaryRequirement(double maxExpectedSalary)
    : maxExpectedSalary(maxExpectedSalary) {}

std::optional<std::string> MaximumExpectedSalaryRequirement::check(const Resume& resume) const {
    if (resume.getExpectedSalary() > maxExpectedSalary) {
        return std::format("{} exceeds the maximum allowed salary expectation of {}.", resume.getExpectedSalary(), maxExpectedSalary);
    }
    return std::nullopt;
}

std::unique_ptr<Requirement> MaximumExpectedSalaryRequirement::clone() const {
    return std::make_unique<MaximumExpectedSalaryRequirement>(*this);
}
