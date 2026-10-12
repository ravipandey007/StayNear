#ifndef PERSON_H
#define PERSON_H

#include <string>

// Base class for every person in StayNear.
// Private data is accessed through public functions (encapsulation).
class Person
{
public:
    Person(const std::string &name, const std::string &phone);
    virtual ~Person() = default;

    const std::string &getName() const;
    const std::string &getPhone() const;
    virtual std::string getRole() const = 0;

protected:
    std::string name_;
    std::string phone_;
};

#endif
