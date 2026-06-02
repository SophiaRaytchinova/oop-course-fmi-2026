#include "SkillRequirement.h"

#include <format>

SkillRequirement::SkillRequirement(const std::string& skill) : expectedSkill(skill) {}

std::optional<std::string> SkillRequirement::check(const Resume& resume) const {
    if (!resume.hasSkill(expectedSkill)) {
        return std::format("Resume does not contain expected skill: {}.", expectedSkill);
    }
    return std::nullopt;
}

std::unique_ptr<Requirement> SkillRequirement::clone() const {
    return std::make_unique<SkillRequirement>(*this);
}
