#include "Student.h"

#include <iomanip>

Student::Student(const std::string& fn, const std::string& name)
    : facultyNumber(fn), name(name) {}

void Student::addSubject(const Subject& subject, double grade) {
    auto it = std::find_if(subjects.begin(), subjects.end(), [&subject](const std::pair<Subject, double>& s) {
        return s.first.getName() == subject.getName();
    });

    if (it == subjects.end()) {
        subjects.push_back(std::make_pair<>(subject, grade));
        credits += subject.getCredits();
        recalculateAverageGrade = true;
    }
}

const std::string& Student::getName() const {
    return name;
}

const std::string& Student::getFacultyNumber() const {
    return facultyNumber;
}

const std::vector<std::pair<Subject, double>>& Student::getSubjects() const {
    return subjects;
}

double Student::getAverageGrade() const {
    static double averageGrade = 0.0;
    if (recalculateAverageGrade) {
        averageGrade = 0.0;
        for (const auto& s : subjects) {
            averageGrade += s.second;
        }
        averageGrade /= subjects.size();
    }
    return averageGrade;
}

size_t Student::getCredits() const {
    return credits;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    return os << student.getName() << ", "
        << "FN: " << student.getFacultyNumber() << ", "
        << "Avg grade: " << std::setprecision(3) << student.getAverageGrade() << ", "
        << "Credits: " << student.getCredits() << '\n';
}
