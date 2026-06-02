#pragma once
#include "Requirement.h"

class MinimumExperienceRequirement : public Requirement {
public:
    explicit MinimumExperienceRequirement(size_t minYears);
    std::optional<std::string> check(const Resume& resume) const override;
    std::unique_ptr<Requirement> clone() const override;
private:
    size_t minYears;
};
