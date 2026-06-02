#include "MinimumExperienceRequirement.h"
#include <format>

MinimumExperienceRequirement::MinimumExperienceRequirement(size_t minYears) : minYears(minYears) {}

std::optional<std::string> MinimumExperienceRequirement::check(const Resume& resume) const {
    if (resume.getYearsOfExperience() < minYears) {
        return std::format("{} is below the expected minimum of {} years of experience.", resume.getYearsOfExperience(),
                           minYears);
    }
    return std::nullopt;
}

std::unique_ptr<Requirement> MinimumExperienceRequirement::clone() const {
    return std::make_unique<MinimumExperienceRequirement>(*this);
}
