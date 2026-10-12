#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include "Student.h"

using namespace std;

// ============================================================================
// CLASS: Room
// Concepts Demonstrated:
//  1. Composition: Room HAS-A collection of Students (vector<Student>).
//  2. Data Validation: Ensures occupied beds do not exceed total capacity.
// ============================================================================
class Room
{
private:
    int roomNumber;
    int totalBeds;
    int occupiedBeds;
    vector<Student> students; // Composition: List of students residing in this room

public:
    // 1. Default Constructor
    Room();

    // 2. Parameterized Constructor
    Room(int roomNumber, int totalBeds);

    // 3. Input and Display Methods
    void input();
    void display() const;

    // 4. Getters
    int getRoomNumber() const;
    int getTotalBeds() const;
    int getOccupiedBeds() const;
    int getAvailableBeds() const;
    const vector<Student>& getStudents() const;

    // 5. Helper Methods
    void setRoomDetails(int rNum, int tBeds);
    bool addStudent(const Student &s);
};

#endif // ROOM_H
