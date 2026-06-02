#include "Resume.h"
#include <algorithm>

Resume::Resume(const std::string& firstName, const std::string& lastName, const std::string& email,
               size_t age, size_t experience, double salary)
    : firstName(firstName), lastName(lastName), email(email), age(age), yearsExperience(experience),
      expectedSalary(salary) {}

Resume::Resume(const std::string& firstName, const std::string& lastName, const std::string& email,
               size_t age, size_t experience, double salary, const std::vector<std::string>& skills)
    : Resume(firstName, lastName, email, age, experience, salary) {
    this->skills = skills;
}

void Resume::addSkill(const std::string& skill) {
    auto it = std::ranges::find(skills, skill);
    if (it == skills.end()) {
        skills.push_back(skill);
    }
}

void Resume::removeSkill(const std::string& skill) {
    auto it = std::ranges::find(skills, skill);
    if (it != skills.end()) {
        skills.erase(it);
    }
}

bool Resume::hasSkill(const std::string& skill) const {
    auto it = std::ranges::find(skills, skill);
    return it != skills.end();
}

const std::string& Resume::getFirstName() const {
    return firstName;
}

const std::string& Resume::getLastName() const {
    return lastName;
}

const std::string& Resume::getEmail() const {
    return email;
}

size_t Resume::getAge() const {
    return age;
}

size_t Resume::getYearsOfExperience() const {
    return yearsExperience;
}

double Resume::getExpectedSalary() const {
    return expectedSalary;
}

const std::vector<std::string>& Resume::getSkills() const {
    return skills;
}

std::ostream& operator<<(std::ostream& os, const Resume& resume) {
    os << resume.getFirstName() << ' ' << resume.getLastName()
        << ", Email: " << resume.getEmail() << ", "
        << "Age: " << resume.getAge()
        << ", Experience: " << resume.getYearsOfExperience()
        << ", Expected salary: " << resume.getExpectedSalary()
        << ", Skills: ";

    for (const std::string& skill : resume.getSkills()) {
        os << skill << ' ';
    }

    return os;
}
