#include "StudentsSystem.h"
#include "AdmissionResult.h"
#include "CustomExceptions.h"
#include <iostream>


StudentsSystem::StudentsSystem(const std::shared_ptr<AdmissionService>& admissionService)
    : admissionService(admissionService) {}

std::optional<Student> StudentsSystem::findByFacultyNumber(const std::string& fn) const {
    auto it = std::ranges::find_if(getStudents(), [&fn](const Student& student) {
        return student.getFacultyNumber() == fn;
    });

    if (it == getStudents().end()) {
        return std::nullopt;
    }

    return *it;
}


void StudentsSystem::addStudent(const Student& student) {
    std::optional<Student> existingStudent = findByFacultyNumber(student.getFacultyNumber());
    if (existingStudent) {
        throw StudentAlreadyExistsException(std::format("Student with fn {} already admitted.", student.getFacultyNumber()));
    }

    AdmissionResult admissionResult = admissionService->check(student);
    if (!admissionResult) {
        const std::vector<std::string>& rejectionReasons = admissionResult.getRejectionReasons();
        for (const auto& rejectionReason : rejectionReasons) {
            std::cout << rejectionReason << std::endl;
        }
        return;
    }

    admittedStudents.push_back(student);
}

std::optional<Student> StudentsSystem::findFirstBy(bool (*predicate)(const Student& student)) const {
    auto it = std::ranges::find_if(admittedStudents, predicate);
    if (it != admittedStudents.end()) {
        return *it;
    }
    return std::nullopt;
}

// std::optional<Student> StudentsSystem::findFirstBy(const std::function<bool(const Student& s)>& predicate) {
//     auto it = std::ranges::find_if(admittedStudents, predicate);
//     if (it != admittedStudents.end()) {
//         return *it;
//     }
//     return std::nullopt;
// }

void StudentsSystem::removeByFacultyNumber(const std::string& fn) {
    auto it = std::ranges::find_if(admittedStudents, [&fn](const Student& s) {
        return s.getFacultyNumber() == fn;
    });

    if (it == admittedStudents.end()) {
        throw StudentNotFoundException(std::format("Student with fn {} not found.", fn));
    }

    admittedStudents.erase(it);
}

// void StudentsSystem::removeAllBy(bool (*predicate)(const Student& student)) {
//     auto removed = std::ranges::remove_if(admittedStudents, predicate);
//     admittedStudents.erase(removed.begin(), removed.end());
// }

void StudentsSystem::removeAllBy(const std::function<bool(const Student& s)>& predicate) {
    auto removed = std::ranges::remove_if(admittedStudents, predicate);
    admittedStudents.erase(removed.begin(), removed.end());
}

const std::vector<Student>& StudentsSystem::getStudents() const {
    return admittedStudents;
}

