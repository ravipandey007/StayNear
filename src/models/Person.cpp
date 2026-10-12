#include "Person.h"

// Save the common name and phone number.
Person::Person(const std::string &name, const std::string &phone)
    : name_(name), phone_(phone)
{
}

const std::string &Person::getName() const
{
    return name_;
}

const std::string &Person::getPhone() const
{
    return phone_;
}
