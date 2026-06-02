#pragma once
#include "Pool.hpp"
#include "Resume.h"
#include <ostream>

class ResumePool : public Pool<Resume> {
public:
    std::optional<Resume> findByEmail(const std::string& email) const;
    std::vector<Resume> filterBySkill(const std::string& skill) const;
    double averageSalary() const;

    friend std::ostream& operator<<(std::ostream& os, const ResumePool& pool);
};
