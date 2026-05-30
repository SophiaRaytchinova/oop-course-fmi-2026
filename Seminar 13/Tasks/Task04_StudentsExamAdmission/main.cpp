#include "AllMandatorySubjectsPassedRequirement.h"
#include "MinimumAverageGrade.h"
#include "MinimumCreditsRequirement.h"
#include "MinimumSubjectsByCategoryRequirement.h"
#include "PassedSubjectsRequirement.h"
#include "Student.h"
#include "StudentsSystem.h"
#include <iostream>

int main() {
    Student s1("fn1", "Student Student");
    Student s2("fn2", "Test test");

    Subject oop("OOP", Subject::Category::PROGRAMMING, 40);
    Subject alg("Algebra", Subject::Category::MATHEMATICS, 40);
    Subject javaCourse("Java", Subject::Category::PROGRAMMING, 50);
    Subject diffEquations("Differential Equations in practice", Subject::Category::APPLIED_MATHEMATICS,
                          25, false);

    s1.addSubject(oop, 2.0);
    s1.addSubject(alg, 4.5);
    s1.addSubject(diffEquations, 5);

    s2.addSubject(oop, 5.5);
    s2.addSubject(javaCourse, 4.5);
    s2.addSubject(diffEquations, 5.5);
    s2.addSubject(alg, 5);

    MinimumSubjectsByCategoryRequirement req1(Subject::Category::PROGRAMMING, 2);
    MinimumSubjectsByCategoryRequirement req2(Subject::Category::MATHEMATICS, 1);
    MinimumCreditsRequirement req3(150);
    MinimumAverageGradeRequirement req4(3.5);
    PassedSubjectsRequirement req5({"OOP", "Java", "Algebra"});
    AllMandatorySubjectsPassedRequirement req6;

    std::shared_ptr<AdmissionService> admissionService = std::make_shared<AdmissionService>();
    admissionService->pushBack(req1);
    admissionService->pushBack(req2);
    admissionService->pushBack(req3);
    admissionService->pushBack(req4);
    admissionService->pushBack(req5);
    admissionService->pushBack(req6);

    StudentsSystem finalExamSystem(admissionService);

    finalExamSystem.addStudent(s1);
    finalExamSystem.addStudent(s2);

    Student s3("fn2", "Duplicate");
    // Duplicate example
    try {
        finalExamSystem.addStudent(s3);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << '\n';
    }

    std::optional<Student> foundByNameAbc = finalExamSystem.findFirstBy([](const Student& s) {
        return s.getName() == "Abc Def";
    });
    if (foundByNameAbc) {
        std::cout << *foundByNameAbc << '\n';
    } else {
        std::cout << "Could not find student with name Abc Def\n";
    }

    try {
        finalExamSystem.removeByFacultyNumber("invalidFn");
    } catch (const std::exception& ex) {
        std::cout << ex.what() << '\n';
    }

    std::function hasExcellentAverageGrade = [] (const Student& s) -> bool {
        return s.getAverageGrade() == 6.0;
    };
    finalExamSystem.removeAllBy(hasExcellentAverageGrade);

    for (const auto& s : finalExamSystem.getStudents()) {
        std::cout << s;
    }
}
