#include "ResumePool.h"

std::optional<Resume> ResumePool::findByEmail(const std::string& email) const {
    // if you capture the email, it is going to require the std::function overload
    return findFirst([&email](const Resume& r) {
        return r.getEmail() == email;
    });

    // alternatively, if you don't have a std::function implementation for the findFirst:
    // for (const Resume& r : items) {
    //     if (r.getEmail() == email) {
    //         return r;
    //     }
    // }
    // return std::nullopt;
}

std::vector<Resume> ResumePool::filterBySkill(const std::string& skill) const {
    return filter([&skill](const Resume& r) {
        const std::vector<std::string>& skills = r.getSkills();
        return std::find(skills.begin(), skills.end(), skill) != skills.end();
    });

    // alternatively, if you don't have a filter implementation with std::function :
    // std::vector<Resume> result;
    // for (const Resume& r : items) {
    //     const auto& skills = r.getSkills();
    //     for (const std::string& s : skills) {
    //         if (s == skill) {
    //             result.push_back(r);
    //             break;
    //         }
    //     }
    // }
    // return result;
}

double ResumePool::averageSalary() const {
    double sum = 0.0;
    for (const auto& resume : items) {
        sum += resume.getExpectedSalary();
    }
    if (items.empty()) {
        return 0.0;
    }
    return sum / items.size();
}

std::ostream& operator<<(std::ostream& os, const ResumePool& pool) {
    for (const Resume& resume : pool.items) {
        os << resume << '\n';
    }
    return os;
}
