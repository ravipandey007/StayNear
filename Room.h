#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include "Student.h"

using namespace std;

class Room
{
private:
    int roomNumber;
    int totalBeds;
    int occupiedBeds;
    Student *students; // Pointer pointing to array of Student objects

public:
    Room();
    ~Room();

    void input();
    void display() const;

    int getRoomNumber() const;
    int getTotalBeds() const;
    int getOccupiedBeds() const;
    int getAvailableBeds() const;
};

#endif