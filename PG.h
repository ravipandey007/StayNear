#ifndef PG_H
#define PG_H

#include <iostream>
#include <string>
#include <vector>
#include "Owner.h"
#include "Room.h"

using namespace std;

// ============================================================================
// CLASS: PG (Paying Guest Accommodation)
// Concepts Demonstrated:
//  1. Composition: PG HAS-A Owner and PG HAS-A collection of Rooms.
//  2. Aggregation: Calculates total, occupied, and available beds dynamically.
// ============================================================================
class PG
{
private:
    string pgName;
    string collegeName;
    string location;
    string pgType; // "Boys", "Girls", "Co-Ed"
    int rent;      // Monthly rent in INR
    float rating;  // Rating (e.g. 4.5 / 5.0)

    Owner owner;         // Composition: Owner instance
    vector<Room> rooms;  // Composition: Vector of Rooms

public:
    // 1. Default Constructor
    PG();

    // 2. Parameterized Constructor
    PG(const string &name, const string &college, const string &loc, 
       const string &type, int rentVal, float ratingVal);

    // 3. Input and Display Methods
    void input();
    void display() const;

    // 4. Getters
    string getPGName() const;
    string getCollegeName() const;
    string getLocation() const;
    string getPGType() const;
    int getRent() const;
    float getRating() const;

    // 5. Aggregate Bed Calculation Methods
    int getAvailableBedsCount() const;
    int getTotalBedsCount() const;
    int getOccupiedBedsCount() const;

    // 6. Access to Rooms and Owner
    int getTotalRooms() const;
    const vector<Room>& getRooms() const;
    const Owner& getOwner() const;

    // 7. Modifiers
    void setPGDetails(const string &name, const string &college, 
                      const string &loc, const string &type, 
                      int rentVal, float ratingVal);
    void setOwner(const Owner &o);
    void addRoom(const Room &r);
};

#endif // PG_H
