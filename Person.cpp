#include "Person.h"

Person::Person()
{
    name = "";
    phone = "";
}

Person::Person(string name, string phone)
{
    this->name = name;
    this->phone = phone;
}

void Person::inputPerson()
{
    cout << "Enter Name: ";
    getline(cin >> ws, name);

    cout << "Enter Phone Number: ";
    getline(cin >> ws, phone);
}

void Person::displayPerson() const
{
    cout << "Name  : " << name << endl;
    cout << "Phone : " << phone << endl;
}

string Person::getName() const
{
    return name;
}

string Person::getPhone() const
{
    return phone;
}
