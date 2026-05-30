#include "MinimumCreditsFromNonMandatorySubjectsRequirement.h"

#include <format>

MinimumCreditsFromNonMandatorySubjectsRequirement::MinimumCreditsFromNonMandatorySubjectsRequirement(size_t minCredits)
    : minCredits(minCredits) {}

std::unique_ptr<AdmissionRequirement> MinimumCreditsFromNonMandatorySubjectsRequirement::clone() const {
    return std::make_unique<MinimumCreditsFromNonMandatorySubjectsRequirement>(*this);
}

std::optional<std::string> MinimumCreditsFromNonMandatorySubjectsRequirement::check(const Student& student) const {
    const std::vector<std::pair<Subject, double>>& passedSubjects = student.getSubjects();
    size_t nonMandatorySubjectsCredits = 0;
    for (const auto& subject : passedSubjects) {
        if (!subject.first.isMandatory()) {
            nonMandatorySubjectsCredits += subject.first.getCredits();
        }
    }

    if (nonMandatorySubjectsCredits < minCredits) {
        return std::format("{} has {} credits from non-mandatory subjects, but at least {} were expected.",
            student.getFacultyNumber(), nonMandatorySubjectsCredits, minCredits);
    }
    return std::nullopt;
}
