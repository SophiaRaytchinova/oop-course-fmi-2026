#pragma once
#include "AdmissionRequirement.h"

class MinimumAverageGradeRequirement : public AdmissionRequirement {
public:
    explicit MinimumAverageGradeRequirement(double minAvgGrade);
    std::optional<std::string> check(const Student& student) const override;
    std::unique_ptr<AdmissionRequirement> clone() const override;

private:
    double minimumGrade;
};
