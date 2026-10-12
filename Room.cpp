#include "Room.h"

// Default constructor
Room::Room()
{
    roomNumber = 0;
    totalBeds = 0;
    occupiedBeds = 0;
}

// Parameterized constructor: starts with 0 occupied beds
Room::Room(int roomNumber, int totalBeds)
{
    this->roomNumber = roomNumber;
    this->totalBeds = totalBeds;
    this->occupiedBeds = 0;
}

// Reads room information and its student details from input
void Room::input()
{
    cout << "\nEnter Room Number: ";
    cin >> roomNumber;

    cout << "Enter Total Beds: ";
    cin >> totalBeds;

    cout << "Enter Occupied Beds: ";
    cin >> occupiedBeds;

    // Validation: Occupied beds cannot exceed total capacity
    if (occupiedBeds > totalBeds)
    {
        cout << "[Note] Occupied beds cannot exceed total capacity. Setting occupied beds to " 
             << totalBeds << ".\n";
        occupiedBeds = totalBeds;
    }

    students.clear();
    for (int i = 0; i < occupiedBeds; i++)
    {
        cout << "\n--- Student " << (i + 1) << " in Room #" << roomNumber << " ---\n";
        Student s;
        s.input();
        students.push_back(s);
    }
}

// Displays room status and lists all students living inside
void Room::display() const
{
    cout << "\n  Room #" << roomNumber
         << " | Total Beds: " << totalBeds
         << " | Occupied: " << occupiedBeds
         << " | Available: " << getAvailableBeds() << endl;

    for (size_t i = 0; i < students.size(); i++)
    {
        students[i].display();
    }
}

// Getters
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

const vector<Student>& Room::getStudents() const
{
    return students;
}

// Set room details directly
void Room::setRoomDetails(int rNum, int tBeds)
{
    roomNumber = rNum;
    totalBeds = tBeds;
}

// Adds a student to this room if a bed is free
bool Room::addStudent(const Student &s)
{
    if (occupiedBeds >= totalBeds)
    {
        return false; // Room is completely full
    }
    students.push_back(s);
    occupiedBeds++;
    return true;
}
