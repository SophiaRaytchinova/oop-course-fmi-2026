#include "MinimumSubjectsByCategoryRequirement.h"
#include <format>

MinimumSubjectsByCategoryRequirement::MinimumSubjectsByCategoryRequirement(Subject::Category subjectCategory, size_t minCount)
    : category(subjectCategory), minCount(minCount) {}

std::unique_ptr<AdmissionRequirement> MinimumSubjectsByCategoryRequirement::clone() const {
    return std::make_unique<MinimumSubjectsByCategoryRequirement>(*this);
}

std::optional<std::string> MinimumSubjectsByCategoryRequirement::check(const Student& student) const {
    const std::vector<std::pair<Subject, double>>& passedSubjects = student.getSubjects();
    Subject::Category expectedCategory = this->category;
    size_t count = std::ranges::count_if(passedSubjects, [&expectedCategory](const std::pair<Subject, double>& subject) {
        if (subject.second < 3.0) {
            return false;
        }
        return subject.first.getCategory() == expectedCategory;
    });
    if (count < minCount) {
        return std::format("{} has passed {} subjects of category {}, but at least {} were expected.",
            student.getFacultyNumber(), count, subjectCategoryToString(expectedCategory), minCount);
    }
    return std::nullopt;
}
