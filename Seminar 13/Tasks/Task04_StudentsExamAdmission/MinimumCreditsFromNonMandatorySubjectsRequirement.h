#pragma once
#include "AdmissionRequirement.h"

class MinimumCreditsFromNonMandatorySubjectsRequirement : public AdmissionRequirement {
public:
    MinimumCreditsFromNonMandatorySubjectsRequirement(size_t minCredits);
    std::optional<std::string> check(const Student& student) const override;
    std::unique_ptr<AdmissionRequirement> clone() const override;

private:
    size_t minCredits;
};
