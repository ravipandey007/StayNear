#ifndef OWNER_H
#define OWNER_H

#include "Person.h"

// ============================================================================
// DERIVED CLASS: Owner
// Concepts Demonstrated:
//  1. Inheritance: Owner IS-A Person (inherits name, phone).
//  2. Code Reusability: Reuses base class input and getters/setters.
//  3. Polymorphism: Overrides display() method.
// ============================================================================
class Owner : public Person
{
private:
    string email; // Owner contact email

public:
    // 1. Default Constructor: Calls base class default constructor
    Owner();

    // 2. Parameterized Constructor: Passes name & phone to Person constructor
    Owner(const string &name, const string &phone, const string &email);

    // 3. Input Method: Reads owner specific details
    void input();

    // 4. Overridden Display Method (Polymorphism)
    void display() const override;

    // 5. Getter for Email
    string getEmail() const;

    // 6. Setter for Email
    void setEmail(const string &e);
};

#endif // OWNER_H
