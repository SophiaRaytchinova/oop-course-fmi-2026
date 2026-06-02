#include <iostream>
#include <vector>
#include <string>

#include "Resume.h"
#include "ResumeSelectionSystem.h"
#include "RequirementFactory.h"
#include "CustomResumeExceptions.h"

int main() {
    // Requirements are loaded from configuration - type and value
    std::vector<RequirementConfiguration> configs = {
        {"min_experience", "3"},
        {"skill", "C++"},
        {"skill", "OOP"},
        {"max_salary", "8000"},
        {"min_age", "21"},
    };

    ResumeSelectionSystem system;

    for (const auto& c : configs) {
        system.addRequirement(RequirementFactory::createRequirement(c));
    }

    // Resume that satisfies all requirements
    Resume r1("John", "Doe", "john.doe@mail.com", 25, 5, 7000.0, {"C++", "OOP", "SQL"});

    ApplicationResult result1 = system.addResume(r1);

    if (result1) {
        std::cout << "Accepted: " << r1 << "\n";
    }

    // Resume that does NOT satisfy the requirements
    Resume r2("Test", "Test", "test.test@mail.com", 19, 1, 9000.0, {"Java"});

    ApplicationResult result2 = system.addResume(r2);

    if (!result2) {
        for (const auto& error : result2.getRejectionReasons()) {
            std::cout << "Rejected: " << error << "\n";
        }
    }

    // Duplicate email
    try {
        ApplicationResult result3 = system.addResume(r1);

        if (!result3) {
            for (const auto& error : result3.getRejectionReasons()) {
                std::cout << error << "\n";
            }
        }
    }
    catch (const ResumeAlreadyExistsException& ex) {
        std::cout << ex.what() << "\n";
    }

    auto found = system.findResumeByEmail("john.doe@mail.com");

    if (found) {
        std::cout << *found << "\n";
    }

    // Filtering through the resume pool
    auto cppDevs = system.getResumes().filterBySkill("C++");
    std::cout << "C++ candidates: " << cppDevs.size() << "\n";

    std::cout << "Average salary: " << system.getResumes().averageSalary() << "\n";

    // Pool with arbitrary type
    Pool<std::string> tags;
    tags.add("senior");
    tags.add("remote");
    tags.add("junior");

    auto senior = tags.filter([](const auto& tag) {
        return tag == "senior";
    });

    std::cout << "Senior tags: " << senior.size() << "\n";

    ResumeSelectionSystem system2 = system;
}
