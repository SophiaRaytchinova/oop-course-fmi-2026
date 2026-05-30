#pragma once
#include "AdmissionRequirement.h"

class PassedSubjectsRequirement : public AdmissionRequirement {
public:
    explicit PassedSubjectsRequirement(const std::vector<std::string>& subjectNames);
    std::optional<std::string> check(const Student& student) const override;
    std::unique_ptr<AdmissionRequirement> clone() const override;

private:
    std::vector<std::string> subjectNames;
};
