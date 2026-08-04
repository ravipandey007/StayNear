#ifndef OWNER_H
#define OWNER_H

#include "Person.h"

// Derived Class: Owner inherits from Person (OOP Inheritance)
class Owner : public Person
{
private:
    string email;

public:
    Owner();

    void input();
    void display() const;

    string getEmail() const;
};

#endif