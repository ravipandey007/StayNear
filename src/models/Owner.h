#ifndef OWNER_H
#define OWNER_H

#include <string>

#include "Person.h"

// Owner inherits the common name and phone number from Person.
class Owner : public Person
{
public:
    Owner(const std::string &name = "", const std::string &phone = "",
          const std::string &email = "");

    const std::string &getEmail() const;
    std::string getRole() const override;

private:
    std::string email_;
};

#endif
