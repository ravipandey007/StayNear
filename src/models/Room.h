#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "Student.h"

// A room owns its list of students and keeps track of its bed capacity.
class Room
{
public:
    Room(int roomNumber, int totalBeds);

    int getRoomNumber() const;
    int getTotalBeds() const;
    int getOccupiedBeds() const;
    int getAvailableBeds() const;
    const std::vector<Student> &getStudents() const;

    bool addStudent(const Student &student);

private:
    int roomNumber_;
    int totalBeds_;
    std::vector<Student> students_;
};

#endif
