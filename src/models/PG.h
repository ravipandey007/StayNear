#ifndef PG_H
#define PG_H

#include <string>
#include <vector>

#include "Owner.h"
#include "Room.h"

// A PG has one owner and a list of rooms.
class PG
{
public:
    PG(const std::string &name, const std::string &college,
       const std::string &location, const std::string &type,
       int rent, float rating);

    const std::string &getPGName() const;
    const std::string &getCollegeName() const;
    const std::string &getLocation() const;
    const std::string &getPGType() const;
    int getRent() const;
    float getRating() const;
    int getTotalRooms() const;
    // These functions hide the bed-count calculations from the rest of the app.
    int getAvailableBedsCount() const;
    int getTotalBedsCount() const;
    int getOccupiedBedsCount() const;
    const std::vector<Room> &getRooms() const;
    const Owner &getOwner() const;

    void setOwner(const Owner &owner);
    void addRoom(const Room &room);

private:
    std::string name_;
    std::string college_;
    std::string location_;
    std::string type_;
    int rent_;
    float rating_;
    Owner owner_;
    std::vector<Room> rooms_;
};

#endif
