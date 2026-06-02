#include "RequirementFactory.h"

#include "MaximumExpectedSalaryRequirement.h"
#include "MinimumAgeRequirement.h"
#include "MinimumExperienceRequirement.h"
#include "SkillRequirement.h"
#include <format>

static size_t convertConfigValueToPositiveNumber(const std::string& value) {
    int result = std::stoi(value);
    if (result < 0) {
        throw std::invalid_argument("Value must be a non-negative number!");
    }
    return result;
}

static double convertConfigValueToPositiveDouble(const std::string& value) {
    double result = std::stod(value);
    if (result < 0) {
        throw std::invalid_argument("Value must be a non-negative floating point number!");
    }
    return result;
}

RequirementConfiguration::RequirementConfiguration(const std::string& type, const std::string& value)
    : requirementType(type), value(value) {}

const std::string& RequirementConfiguration::getType() const {
    return requirementType;
}

const std::string& RequirementConfiguration::getValue() const {
    return value;
}

std::unique_ptr<Requirement> RequirementFactory::createRequirement(const RequirementConfiguration& config) {
    const std::string& type = config.getType();

    if (type == "min_experience") {
        return std::make_unique<MinimumExperienceRequirement>(convertConfigValueToPositiveNumber(config.getValue()));
    }
    if (type == "min_age") {
        return std::make_unique<MinimumAgeRequirement>(convertConfigValueToPositiveNumber(config.getValue()));
    }
    if (type == "max_salary") {
        return std::make_unique<MaximumExpectedSalaryRequirement>(convertConfigValueToPositiveDouble(config.getValue()));
    }
    if (type == "skill") {
        return std::make_unique<SkillRequirement>(config.getValue());
    }
    throw std::invalid_argument(std::format("Invalid requirement type {}!", type));
}
