#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

// Derived Class: Student inherits from Person (OOP Inheritance)
class Student : public Person
{
private:
    string course;
    int year;

public:
    Student();

    void input();
    void display() const;

    string getCourse() const;
    int getYear() const;
};

#endif