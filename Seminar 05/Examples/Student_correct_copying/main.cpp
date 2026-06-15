#include "Student.h"

int main() {
    //...
    Student s("John Doe");
    s.addGrade(5.50);
    s.addGrade(6.00);
    s.addGrade(3.25);
    printStudent(s);

    {
        Student copy = s;
        copy.addGrade(6.00);
        printStudent(copy);
    }

    printStudent(s);
}
