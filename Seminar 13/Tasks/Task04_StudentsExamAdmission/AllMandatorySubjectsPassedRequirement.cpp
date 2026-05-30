#include "AllMandatorySubjectsPassedRequirement.h"
#include <format>

std::unique_ptr<AdmissionRequirement> AllMandatorySubjectsPassedRequirement::clone() const {
    return std::make_unique<AllMandatorySubjectsPassedRequirement>(*this);
}

std::optional<std::string> AllMandatorySubjectsPassedRequirement::check(const Student& student) const {
    const auto& subjects = student.getSubjects();
    for (const auto& s : subjects) {
        if (s.first.isMandatory() && s.second < 3.0) {
            return std::format("{} has not passed all mandatory subjects.", student.getFacultyNumber());
        }
    }
    return std::nullopt;
}
