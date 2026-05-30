#pragma once
#include <string>

class Subject {
public:

    enum class Category {
        PROGRAMMING,
        MATHEMATICS,
        APPLIED_MATHEMATICS,
        OTHER
    };

    Subject(const std::string& name, Category category, unsigned credits, bool mandatory = true);

    const std::string& getName() const;
    unsigned getCredits() const;
    bool isMandatory() const;
    Category getCategory() const;

private:
    std::string name;
    Category category;
    unsigned credits;
    bool mandatory;
};

std::string subjectCategoryToString(Subject::Category category);
