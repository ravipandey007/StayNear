#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

// ============================================================================
// BASE CLASS: Person
// Concepts Demonstrated:
//  1. Encapsulation: Attributes are protected (accessible by child classes).
//  2. Polymorphism: Virtual display() method allows derived classes to override.
// ============================================================================
class Person
{
protected:
    // Protected member variables:
    // Accessible by this class and derived classes (Student, Owner),
    // but hidden from outside functions.
    string name;
    string phone;

public:
    // 1. Default Constructor: Initializes variables with empty values
    Person();

    // 2. Parameterized Constructor: Sets initial name and phone number
    Person(const string &name, const string &phone);

    // 3. Virtual Destructor: Ensures proper cleanup of derived objects
    virtual ~Person() = default;

    // 4. Input Method: Takes input from console
    void inputPerson();

    // 5. Virtual Display Method: Demonstrates Runtime Polymorphism (can be overridden)
    virtual void display() const;

    // 6. Getters: Read-only access to private/protected data
    string getName() const;
    string getPhone() const;

    // 7. Setters: Controlled modification of data
    void setName(const string &n);
    void setPhone(const string &p);
};

#endif // PERSON_H
