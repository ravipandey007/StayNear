#include "PG.h"

PG::PG()
{
    pgName = "";
    collegeName = "Graphic Era Hill University Bhimtal";
    location = "Bhimtal, Uttarakhand";
    pgType = "Boys";
    rent = 0;
    rating = 0.0;
    totalRooms = 0;
    rooms = nullptr;
}

PG::~PG()
{
    // Clean up dynamic memory pointer
    if (rooms != nullptr)
    {
        delete[] rooms;
    }
}

void PG::input()
{
    cout << "\nEnter PG Name: ";
    getline(cin >> ws, pgName);

    cout << "Enter Nearby College (Default: Graphic Era Hill University Bhimtal): ";
    getline(cin >> ws, collegeName);

    cout << "Enter Location in Bhimtal (e.g. Bhowali Road / June Estate): ";
    getline(cin >> ws, location);

    cout << "Enter PG Type (Boys / Girls): ";
    getline(cin >> ws, pgType);

    cout << "Enter Monthly Rent per bed (in Rs): ";
    cin >> rent;

    cout << "Enter Rating (0.0 to 5.0): ";
    cin >> rating;

    // Input Owner Details
    owner.input();

    // Input Rooms
    cout << "\nEnter Total Number of Rooms in PG: ";
    cin >> totalRooms;

    if (totalRooms > 0)
    {
        rooms = new Room[totalRooms];
        for (int i = 0; i < totalRooms; i++)
        {
            cout << "\n=== ROOM " << (i + 1) << " ===\n";
            rooms[i].input();
        }
    }
}

void PG::display() const
{
    cout << "\n==========================================";
    cout << "\nPG Name       : " << pgName;
    cout << "\nCollege       : " << collegeName;
    cout << "\nLocation      : " << location;
    cout << "\nPG Type       : " << pgType;
    cout << "\nMonthly Rent  : Rs. " << rent;
    cout << "\nRating        : " << rating << " / 5.0";

    owner.display();

    cout << "\nTotal Rooms   : " << totalRooms;
    cout << "\nAvailable Beds: " << getAvailableBedsCount() << endl;

    for (int i = 0; i < totalRooms; i++)
    {
        rooms[i].display();
    }
    cout << "==========================================\n";
}

string PG::getPGName() const
{
    return pgName;
}

string PG::getCollegeName() const
{
    return collegeName;
}

string PG::getLocation() const
{
    return location;
}

string PG::getPGType() const
{
    return pgType;
}

int PG::getRent() const
{
    return rent;
}

float PG::getRating() const
{
    return rating;
}

int PG::getAvailableBedsCount() const
{
    int totalAvailable = 0;
    for (int i = 0; i < totalRooms; i++)
    {
        totalAvailable += rooms[i].getAvailableBeds();
    }
    return totalAvailable;
}