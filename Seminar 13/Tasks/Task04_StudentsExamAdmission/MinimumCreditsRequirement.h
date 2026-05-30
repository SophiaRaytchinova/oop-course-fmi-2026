#pragma once
#include "AdmissionRequirement.h"

class MinimumCreditsRequirement : public AdmissionRequirement {
public:
    explicit MinimumCreditsRequirement(size_t minCredits);
    std::optional<std::string> check(const Student& student) const override;
    std::unique_ptr<AdmissionRequirement> clone() const override;

private:
    size_t minCredits;
};
