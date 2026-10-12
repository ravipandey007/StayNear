#include "PG.h"

// Default constructor
PG::PG()
{
    pgName = "";
    collegeName = "Graphic Era Hill University Bhimtal";
    location = "Bhimtal, Uttarakhand";
    pgType = "Boys";
    rent = 0;
    rating = 0.0f;
}

// Parameterized constructor
PG::PG(const string &name, const string &college, const string &loc,
       const string &type, int rentVal, float ratingVal)
{
    pgName = name;
    collegeName = college;
    location = loc;
    pgType = type;
    rent = rentVal;
    rating = ratingVal;
}

// Takes user input for all PG parameters
void PG::input()
{
    cout << "\nEnter PG Name: ";
    getline(cin >> ws, pgName);

    cout << "Enter Nearby College (e.g. Graphic Era / BIAS): ";
    getline(cin >> ws, collegeName);

    cout << "Enter Location in Bhimtal (e.g. Bhowali Road / June Estate): ";
    getline(cin >> ws, location);

    cout << "Enter PG Type (Boys / Girls / Co-Ed): ";
    getline(cin >> ws, pgType);

    cout << "Enter Monthly Rent per bed (in Rs): ";
    cin >> rent;

    cout << "Enter Rating (0.0 to 5.0): ";
    cin >> rating;

    // Input Owner details
    owner.input();

    // Input Room details
    int roomCount;
    cout << "\nEnter Total Number of Rooms in PG: ";
    cin >> roomCount;

    rooms.clear();
    for (int i = 0; i < roomCount; i++)
    {
        cout << "\n=== ROOM " << (i + 1) << " ===\n";
        Room r;
        r.input();
        rooms.push_back(r);
    }
}

// Displays PG information and all associated rooms
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

    cout << "\nTotal Rooms   : " << rooms.size();
    cout << "\nAvailable Beds: " << getAvailableBedsCount() << endl;

    for (size_t i = 0; i < rooms.size(); i++)
    {
        rooms[i].display();
    }
    cout << "==========================================\n";
}

// Getters
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

// Total beds available for new students
int PG::getAvailableBedsCount() const
{
    int count = 0;
    for (size_t i = 0; i < rooms.size(); i++)
    {
        count += rooms[i].getAvailableBeds();
    }
    return count;
}

// Total capacity of the PG
int PG::getTotalBedsCount() const
{
    int count = 0;
    for (size_t i = 0; i < rooms.size(); i++)
    {
        count += rooms[i].getTotalBeds();
    }
    return count;
}

// Total currently occupied beds
int PG::getOccupiedBedsCount() const
{
    int count = 0;
    for (size_t i = 0; i < rooms.size(); i++)
    {
        count += rooms[i].getOccupiedBeds();
    }
    return count;
}

int PG::getTotalRooms() const
{
    return static_cast<int>(rooms.size());
}

const vector<Room>& PG::getRooms() const
{
    return rooms;
}

const Owner& PG::getOwner() const
{
    return owner;
}

// Set basic details
void PG::setPGDetails(const string &name, const string &college, 
                      const string &loc, const string &type, 
                      int rentVal, float ratingVal)
{
    pgName = name;
    collegeName = college;
    location = loc;
    pgType = type;
    rent = rentVal;
    rating = ratingVal;
}

// Set owner instance
void PG::setOwner(const Owner &o)
{
    owner = o;
}

// Add a room to the PG's collection
void PG::addRoom(const Room &r)
{
    rooms.push_back(r);
}
