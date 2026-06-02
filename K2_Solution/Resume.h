#pragma once
#include <string>
#include <vector>
#include <ostream>

class Resume {
public:
    Resume(const std::string& firstName, const std::string& lastName, const std::string& email,
           size_t age, size_t experience, double salary);

    Resume(const std::string& firstName, const std::string& lastName, const std::string& email,
           size_t age, size_t experience, double salary, const std::vector<std::string>& skills);

    void addSkill(const std::string& skill);
    void removeSkill(const std::string& skill);
    bool hasSkill(const std::string& skill) const;

    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getEmail() const;
    size_t getAge() const;
    size_t getYearsOfExperience() const;
    double getExpectedSalary() const;
    const std::vector<std::string>& getSkills() const;

private:
    std::string firstName;
    std::string lastName;
    std::string email;
    size_t age = 0;
    size_t yearsExperience = 0;
    double expectedSalary = 0;
    std::vector<std::string> skills;
};

std::ostream& operator<<(std::ostream& os, const Resume& resume);
