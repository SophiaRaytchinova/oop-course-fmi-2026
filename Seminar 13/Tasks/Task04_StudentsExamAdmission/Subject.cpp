#include "Subject.h"

Subject::Subject(const std::string& name, Category category, unsigned credits, bool mandatory)
    : name(name), credits(credits), mandatory(mandatory), category(category) {}

const std::string& Subject::getName() const {
    return name;
}

unsigned Subject::getCredits() const {
    return credits;
}

bool Subject::isMandatory() const {
    return mandatory;
}

Subject::Category Subject::getCategory() const {
    return category;
}

std::string subjectCategoryToString(Subject::Category category) {
    switch (category) {
        case Subject::Category::PROGRAMMING:
            return "Programming";
        case Subject::Category::MATHEMATICS:
            return "Mathematics";
        case Subject::Category::APPLIED_MATHEMATICS:
            return "Applied Mathematics";
        default:
            return "Other";
    }
}
