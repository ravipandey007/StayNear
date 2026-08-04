#include "Owner.h"

Owner::Owner() : Person()
{
    email = "";
}

void Owner::input()
{
    cout << "\n--- Enter PG Owner Details ---\n";
    // Call base class input
    inputPerson();

    cout << "Enter Owner Email: ";
    getline(cin >> ws, email);
}

void Owner::display() const
{
    cout << "\n--- Owner Info ---\n";
    displayPerson();
    cout << "Email : " << email << endl;
}

string Owner::getEmail() const
{
    return email;
}