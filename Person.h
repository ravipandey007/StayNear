#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

// Base Class: Person (Demonstrates Inheritance for PBL Project)
class Person
{
protected:
    string name;
    string phone;

public:
    Person();
    Person(string name, string phone);

    void inputPerson();
    void displayPerson() const;

    string getName() const;
    string getPhone() const;
};

#endif
