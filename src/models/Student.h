#ifndef STUDENT_H
#define STUDENT_H

#include <string>

#include "Person.h"

// Student inherits the name and phone number from Person.
class Student : public Person
{
private:
    std::string course_;
    int year_;

public:
    Student(const std::string &name, const std::string &phone,
            const std::string &course, int year);

    const std::string &getCourse() const;
    int getYear() const;

    // This version is called when a Person is actually a Student.
    std::string getRole() const override;
};

#endif // STUDENT_H
