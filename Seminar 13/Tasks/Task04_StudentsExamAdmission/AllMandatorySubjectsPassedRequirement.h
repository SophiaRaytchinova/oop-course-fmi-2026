#pragma once
#include "AdmissionRequirement.h"

class AllMandatorySubjectsPassedRequirement : public AdmissionRequirement {
public:
    std::optional<std::string> check(const Student& student) const override;
    std::unique_ptr<AdmissionRequirement> clone() const override;
};
