#pragma once
#include "Requirement.h"

class SkillRequirement : public Requirement {
public:
    explicit SkillRequirement(const std::string& skill);
    std::optional<std::string> check(const Resume& resume) const override;
    std::unique_ptr<Requirement> clone() const override;
private:
    std::string expectedSkill;
};
