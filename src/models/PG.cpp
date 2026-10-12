#include "PG.h"

// Save the basic PG information. Owner and rooms are added separately.
PG::PG(const std::string &name, const std::string &college,
       const std::string &location, const std::string &type,
       int rent, float rating)
    : name_(name),
      college_(college),
      location_(location),
      type_(type),
      rent_(rent),
      rating_(rating)
{
}

const std::string &PG::getPGName() const
{
    return name_;
}

const std::string &PG::getCollegeName() const
{
    return college_;
}

const std::string &PG::getLocation() const
{
    return location_;
}

const std::string &PG::getPGType() const
{
    return type_;
}

int PG::getRent() const
{
    return rent_;
}

float PG::getRating() const
{
    return rating_;
}

int PG::getTotalRooms() const
{
    return static_cast<int>(rooms_.size());
}

int PG::getAvailableBedsCount() const
{
    int count = 0;
    // Ask each room for its available beds and add them together.
    for (const Room &room : rooms_)
    {
        count += room.getAvailableBeds();
    }
    return count;
}

int PG::getTotalBedsCount() const
{
    int count = 0;
    for (const Room &room : rooms_)
    {
        count += room.getTotalBeds();
    }
    return count;
}

int PG::getOccupiedBedsCount() const
{
    int count = 0;
    for (const Room &room : rooms_)
    {
        count += room.getOccupiedBeds();
    }
    return count;
}

const std::vector<Room> &PG::getRooms() const
{
    return rooms_;
}

const Owner &PG::getOwner() const
{
    return owner_;
}

void PG::setOwner(const Owner &owner)
{
    owner_ = owner;
}

void PG::addRoom(const Room &room)
{
    rooms_.push_back(room);
}
