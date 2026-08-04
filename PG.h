#ifndef PG_H
#define PG_H

#include <iostream>
#include <string>

#include "Owner.h"
#include "Room.h"

using namespace std;

class PG
{
private:
    string pgName;
    string collegeName;
    string location;
    string pgType;

    int rent;
    float rating;

    Owner owner;      // Composition (Owner object inside PG)
    
    int totalRooms;
    Room *rooms;      // Pointer pointing to dynamic array of Room objects

public:
    PG();
    ~PG();

    void input();
    void display() const;

    string getPGName() const;
    string getCollegeName() const;
    string getLocation() const;
    string getPGType() const;
    int getRent() const;
    float getRating() const;
    int getAvailableBedsCount() const;
};

#endif