#ifndef REALSTATE_H
#define REALSTATE_H

#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <stdexcept>
#include <regex>

struct RealEstate {
    std::string owner;
    std::tm registrationDate;
    int estimatedCost;
    std::string address;
    int numberOfRooms;

    void parse(const std::string &description);
};

#endif // REALSTATE_H
