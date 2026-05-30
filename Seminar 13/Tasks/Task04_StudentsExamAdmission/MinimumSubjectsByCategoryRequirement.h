#pragma once
#include "AdmissionRequirement.h"

class MinimumSubjectsByCategoryRequirement : public AdmissionRequirement {
public:
    explicit MinimumSubjectsByCategoryRequirement(Subject::Category subjectCategory, size_t minCount);
    std::optional<std::string> check(const Student& student) const override;
    std::unique_ptr<AdmissionRequirement> clone() const override;

private:
    Subject::Category category;
    size_t minCount;
};
