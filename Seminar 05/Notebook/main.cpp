#include <iostream>
#include "Notebook.h"

using namespace std;

int main() {
    Notebook notebook("OOP Notebook", 5);
    notebook.appendToPage(0, "Intro to OOP\nAbstraction, Encapsulation, Inheritance, Polymorphism");
    notebook.appendToPage(1, "Classes and objects...");

    Notebook copy = notebook;
    copy.setTitle("copy of notebook");
    printNotebook(copy);

    printNotebook(notebook);
}
