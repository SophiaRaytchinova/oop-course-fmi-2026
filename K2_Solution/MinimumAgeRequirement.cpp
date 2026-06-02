#include "MinimumAgeRequirement.h"

#include <format>

MinimumAgeRequirement::MinimumAgeRequirement(size_t minAge) : minAge(minAge) {}

std::optional<std::string> MinimumAgeRequirement::check(const Resume& resume) const {
    if (resume.getAge() < minAge) {
        return std::format("{} is below the minimum allowed age of {}.", resume.getAge(), minAge);
    }
    return std::nullopt;
}

std::unique_ptr<Requirement> MinimumAgeRequirement::clone() const {
    return std::make_unique<MinimumAgeRequirement>(*this);
}
