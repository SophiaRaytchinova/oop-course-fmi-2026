#include "MinimumAverageGradeRequirement.h"

#include <format>

constexpr double EPSILON = 10e-9;

MinimumAverageGradeRequirement::MinimumAverageGradeRequirement(double minAvgGrade) : minimumGrade(minAvgGrade) {}

std::unique_ptr<AdmissionRequirement> MinimumAverageGradeRequirement::clone() const {
    return std::make_unique<MinimumAverageGradeRequirement>(*this);
}

std::optional<std::string> MinimumAverageGradeRequirement::check(const Student& student) const {
    if (abs(student.getAverageGrade() - minimumGrade) < EPSILON) {
        return std::format("{} average grade is {:.2f}, but at least {:.2f} is required.",
            student.getFacultyNumber(), student.getAverageGrade(), minimumGrade);
    }
    return std::nullopt;
}
