#include "Room.h"

Room::Room()
{
    roomNumber = 0;
    totalBeds = 0;
    occupiedBeds = 0;
    students = nullptr;
}

Room::~Room()
{
    // Clean up dynamic memory pointer
    if (students != nullptr)
    {
        delete[] students;
    }
}

void Room::input()
{
    cout << "\nEnter Room Number: ";
    cin >> roomNumber;

    cout << "Enter Total Beds: ";
    cin >> totalBeds;

    cout << "Enter Occupied Beds: ";
    cin >> occupiedBeds;

    if (occupiedBeds > totalBeds)
    {
        cout << "Occupied beds cannot exceed total beds. Setting to " << totalBeds << endl;
        occupiedBeds = totalBeds;
    }

    // Dynamic memory allocation using pointers
    if (occupiedBeds > 0)
    {
        students = new Student[occupiedBeds];
        for (int i = 0; i < occupiedBeds; i++)
        {
            cout << "\nStudent " << (i + 1) << " in Room #" << roomNumber << ":\n";
            students[i].input();
        }
    }
}

void Room::display() const
{
    cout << "\n------------------------------------";
    cout << "\nRoom #" << roomNumber 
         << " | Total Beds: " << totalBeds 
         << " | Occupied: " << occupiedBeds 
         << " | Available: " << getAvailableBeds() << endl;

    for (int i = 0; i < occupiedBeds; i++)
    {
        students[i].display();
    }
    cout << "------------------------------------\n";
}

int Room::getRoomNumber() const
{
    return roomNumber;
}

int Room::getTotalBeds() const
{
    return totalBeds;
}

int Room::getOccupiedBeds() const
{
    return occupiedBeds;
}

int Room::getAvailableBeds() const
{
    return totalBeds - occupiedBeds;
}