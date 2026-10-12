#include "Owner.h"

// Default constructor
Owner::Owner() : Person()
{
    email = "";
}

// Parameterized constructor: Delegates (name, phone) to base class Person
Owner::Owner(const string &name, const string &phone, const string &email)
    : Person(name, phone)
{
    this->email = email;
}

// Input method: Reuses base class inputPerson(), then asks for email
void Owner::input()
{
    cout << "\n--- Enter PG Owner Details ---\n";
    inputPerson(); // Reusing base class functionality

    cout << "Enter Owner Email: ";
    getline(cin >> ws, email);
}

// Overridden display method: Shows owner information cleanly
void Owner::display() const
{
    cout << "\nOwner Name    : " << name;
    cout << "\nOwner Contact : " << phone;
    cout << "\nOwner Email   : " << email << endl;
}

// Getter for Email
string Owner::getEmail() const
{
    return email;
}

// Setter for Email
void Owner::setEmail(const string &e)
{
    email = e;
}
