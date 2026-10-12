#include "Room.h"

// A new room starts with no students.
Room::Room(int roomNumber, int totalBeds)
    : roomNumber_(roomNumber), totalBeds_(totalBeds)
{
}

int Room::getRoomNumber() const
{
    return roomNumber_;
}

int Room::getTotalBeds() const
{
    return totalBeds_;
}

int Room::getOccupiedBeds() const
{
    // Each student in the room uses one bed.
    return static_cast<int>(students_.size());
}

int Room::getAvailableBeds() const
{
    return totalBeds_ - getOccupiedBeds();
}

const std::vector<Student> &Room::getStudents() const
{
    return students_;
}

bool Room::addStudent(const Student &student)
{
    // Do not put more students in a room than it has beds.
    if (getAvailableBeds() == 0)
    {
        return false;
    }

    students_.push_back(student);
    return true;
}
