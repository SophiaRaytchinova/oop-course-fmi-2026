#pragma once
#include <memory>
#include <string>
#include "Requirement.h"

// alternatively instead of RequirementConfig, this can be done with std::pair<std::string, std::string>
class RequirementConfiguration {
public:
    RequirementConfiguration(const std::string& type, const std::string& value);

    const std::string& getType() const;
    const std::string& getValue() const;

private:
    std::string requirementType;
    std::string value;
};

class RequirementFactory {
public:
    RequirementFactory() = delete;
    static std::unique_ptr<Requirement> createRequirement(const RequirementConfiguration& config);
};
