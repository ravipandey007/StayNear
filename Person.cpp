#include "Person.h"

// Default constructor: assigns default empty strings
Person::Person()
{
    name = "";
    phone = "";
}

// Parameterized constructor: assigns values passed by caller
Person::Person(const string &name, const string &phone)
{
    this->name = name;
    this->phone = phone;
}

// Reads person information from standard input
void Person::inputPerson()
{
    cout << "Enter Name: ";
    getline(cin >> ws, name); // Discards leading whitespace

    cout << "Enter Phone Number: ";
    getline(cin >> ws, phone);
}

// Displays person information to console
void Person::display() const
{
    cout << "Name  : " << name << endl;
    cout << "Phone : " << phone << endl;
}

// Getter for Name
string Person::getName() const
{
    return name;
}

// Getter for Phone
string Person::getPhone() const
{
    return phone;
}

// Setter for Name
void Person::setName(const string &n)
{
    name = n;
}

// Setter for Phone
void Person::setPhone(const string &p)
{
    phone = p;
}
