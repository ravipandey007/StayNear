#include "Student.h"

Student::Student(const std::string &name, const std::string &phone,
                 const std::string &course, int year)
    : Person(name, phone), course_(course), year_(year)
{
}

const std::string &Student::getCourse() const
{
    return course_;
}

int Student::getYear() const
{
    return year_;
}

std::string Student::getRole() const
{
    return "Student";
}
