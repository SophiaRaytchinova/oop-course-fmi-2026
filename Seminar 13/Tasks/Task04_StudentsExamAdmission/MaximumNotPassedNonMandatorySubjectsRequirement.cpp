#include "MaximumNotPassedNonMandatorySubjectsRequirement.h"
#include <format>

MaximumNotPassedNonMandatorySubjectsRequirement::MaximumNotPassedNonMandatorySubjectsRequirement(size_t maxCount)
    : maxCount(maxCount) {}

std::unique_ptr<AdmissionRequirement> MaximumNotPassedNonMandatorySubjectsRequirement::clone() const {
    return std::make_unique<MaximumNotPassedNonMandatorySubjectsRequirement>(*this);
}

std::optional<std::string> MaximumNotPassedNonMandatorySubjectsRequirement::check(const Student& student) const {
    const std::vector<std::pair<Subject, double>>& subjects = student.getSubjects();
    size_t count = std::count_if(subjects.begin(), subjects.end(), [](const auto& subject) {
       return subject.first.isMandatory() && subject.second > 3.0;
    });
    if (count > maxCount) {
        return std::format("{} has {} non-mandatory courses not passed, but the most allowed is {}.",
            student.getFacultyNumber(), count, maxCount);
    }
    return std::nullopt;
}
