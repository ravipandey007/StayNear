#include "Student.h"

Student::Student() : Person()
{
    course = "";
    year = 0;
}

void Student::input()
{
    cout << "\n--- Enter Student Details ---\n";
    // Call base class input
    inputPerson();

    cout << "Enter Course (e.g. B.Tech / BCA): ";
    getline(cin >> ws, course);

    cout << "Enter Academic Year (1-4): ";
    cin >> year;
}

void Student::display() const
{
    cout << "  [Student] ";
    displayPerson();
    cout << "  Course: " << course << " | Year: " << year << endl;
}

string Student::getCourse() const
{
    return course;
}

int Student::getYear() const
{
    return year;
}