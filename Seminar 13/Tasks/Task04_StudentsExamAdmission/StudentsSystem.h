#pragma once
#include <complex>
#include <functional>
#include <vector>

#include "AdmissionService.h"
#include "Student.h"

class StudentsSystem {
public:
    explicit StudentsSystem(const std::shared_ptr<AdmissionService>& admissionService);

    void addStudent(const Student& student);

    void removeByFacultyNumber(const std::string& fn);
    // void removeAllBy(bool (*predicate)(const Student& student));
    void removeAllBy(const std::function<bool(const Student& s)>& predicate);

    std::optional<Student> findByFacultyNumber(const std::string& fn) const;
    std::optional<Student> findFirstBy(bool (*predicate)(const Student& student)) const;
    // std::optional<Student> findFirstBy(const std::function<bool(const Student& s)>& predicate);

    const std::vector<Student>& getStudents() const;

private:
    std::vector<Student> admittedStudents;
    std::shared_ptr<AdmissionService> admissionService;
};
