#pragma once
#include "Requirement.h"

class MinimumAgeRequirement : public Requirement {
public:
    explicit MinimumAgeRequirement(size_t minAge);
    std::optional<std::string> check(const Resume& resume) const override;
    std::unique_ptr<Requirement> clone() const override;
private:
    size_t minAge;
};
