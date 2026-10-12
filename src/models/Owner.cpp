#include "Owner.h"

Owner::Owner(const std::string &name, const std::string &phone,
             const std::string &email)
    : Person(name, phone), email_(email)
{
}

const std::string &Owner::getEmail() const
{
    return email_;
}

std::string Owner::getRole() const
{
    return "PG Owner";
}
