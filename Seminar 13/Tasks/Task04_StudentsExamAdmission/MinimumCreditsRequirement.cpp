#include "MinimumCreditsRequirement.h"
#include <format>

MinimumCreditsRequirement::MinimumCreditsRequirement(size_t minCredits) : minCredits(minCredits) {}

std::unique_ptr<AdmissionRequirement> MinimumCreditsRequirement::clone() const {
    return std::make_unique<MinimumCreditsRequirement>(*this);
}

std::optional<std::string> MinimumCreditsRequirement::check(const Student& student) const {
    if (minCredits > student.getCredits()) {
        return std::format("{} has {} credits, but at least {} are required.",
            student.getFacultyNumber(), student.getCredits(), minCredits);
    }
    return std::nullopt;
}
