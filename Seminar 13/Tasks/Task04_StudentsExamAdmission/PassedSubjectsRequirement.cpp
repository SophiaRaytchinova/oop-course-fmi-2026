#include "PassedSubjectsRequirement.h"

#include <format>

PassedSubjectsRequirement::PassedSubjectsRequirement(const std::vector<std::string>& subjectNames)
    : subjectNames(subjectNames) {}

std::unique_ptr<AdmissionRequirement> PassedSubjectsRequirement::clone() const {
    return std::make_unique<PassedSubjectsRequirement>(*this);
}

std::optional<std::string> PassedSubjectsRequirement::check(const Student& student) const {
    for (const auto& name : subjectNames) {
        const auto& subjects = student.getSubjects();
        auto it = std::ranges::find_if(subjects, [&name](const std::pair<Subject, double>& s) {
            return s.first.getName() == name;
        });

        if (it == subjects.end()) {
            return std::format("{} has not passed subject {}.", student.getFacultyNumber(), name);
        }
    }
    return std::nullopt;
}
