#pragma once
#include <string>
#include <vector>
#include "Subject.h"

class Student {
public:
    Student(const std::string& fn, const std::string& name);

    void addSubject(const Subject& subject, double grade);

    const std::string& getFacultyNumber() const;
    const std::string& getName() const;
    const std::vector<std::pair<Subject, double>>& getSubjects() const;
    size_t getCredits() const;
    double getAverageGrade() const;

private:
    std::string facultyNumber;
    std::string name;
    size_t credits = 0;

    // each student has a vector of pairs
    // each pair has the subject and the grade which they have earned for that subject
    std::vector<std::pair<Subject, double>> subjects;
    bool recalculateAverageGrade = false;
};

std::ostream& operator<<(std::ostream& os, const Student& student);
