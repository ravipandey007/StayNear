#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

// ============================================================================
// DERIVED CLASS: Student
// Concepts Demonstrated:
//  1. Inheritance: Student IS-A Person (inherits name, phone).
//  2. Code Reusability: Reuses base class input and getters/setters.
//  3. Polymorphism: Overrides display() method.
// ============================================================================
class Student : public Person
{
private:
    string course; // e.g. "B.Tech CSE", "BCA"
    int year;      // Academic year (1, 2, 3, or 4)

public:
    // 1. Default Constructor: Calls base class default constructor
    Student();

    // 2. Parameterized Constructor: Passes name & phone to Person constructor
    Student(const string &name, const string &phone, const string &course, int year);

    // 3. Input Method: Reads student specific details
    void input();

    // 4. Overridden Display Method (Polymorphism)
    void display() const override;

    // 5. Getters
    string getCourse() const;
    int getYear() const;

    // 6. Setters
    void setCourse(const string &c);
    void setYear(int y);
};

#endif // STUDENT_H
