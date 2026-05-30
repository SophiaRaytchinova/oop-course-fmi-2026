#pragma once
#include "AdmissionRequirement.h"

class MaximumNotPassedNonMandatorySubjectsRequirement : public AdmissionRequirement {
public:
    MaximumNotPassedNonMandatorySubjectsRequirement(size_t maxCount);
    std::optional<std::string> check(const Student& student) const override;
    std::unique_ptr<AdmissionRequirement> clone() const override;

private:
    size_t maxCount;
};
