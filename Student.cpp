#include "Student.h"

// Default constructor
Student::Student() : Person()
{
    course = "";
    year = 0;
}

// Parameterized constructor: Delegates (name, phone) to base class Person
Student::Student(const string &name, const string &phone, const string &course, int year)
    : Person(name, phone)
{
    this->course = course;
    this->year = year;
}

// Input method: Reuses base class inputPerson(), then asks for student details
void Student::input()
{
    cout << "\n--- Enter Student Details ---\n";
    inputPerson(); // Reusing base class functionality

    cout << "Enter Course (e.g. B.Tech CSE / BCA): ";
    getline(cin >> ws, course);

    cout << "Enter Academic Year (1-4): ";
    cin >> year;
}

// Overridden display method: Shows student information cleanly
void Student::display() const
{
    cout << "    [Student] Name: " << name
         << " | Phone: " << phone
         << " | Course: " << course
         << " | Year: " << year << endl;
}

// Getter for Course
string Student::getCourse() const
{
    return course;
}

// Getter for Year
int Student::getYear() const
{
    return year;
}

// Setter for Course
void Student::setCourse(const string &c)
{
    course = c;
}

// Setter for Year
void Student::setYear(int y)
{
    year = y;
}
