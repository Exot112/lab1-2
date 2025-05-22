#include "realestatemanager.h"
#include "logger.h"
#include <sstream>

void RealEstateManager::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    objects.clear();
    std::string line;
    int lineNumber = 1;
    while (std::getline(file, line)) {
        try {
            RealEstate obj;
            obj.parse(line);
            objects.push_back(obj);
        } catch (const std::exception &e) {
            log << "Ошибка в строке " << lineNumber << ": " << line << " (" << e.what() << ")\n";
        }
        ++lineNumber;
    }
}


/*void RealEstateManager::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    objects.clear();
    std::string line;
    while (std::getline(file, line)) {
        RealEstate obj;
        obj.parse(line);
        objects.push_back(obj);
    }
}*/

/*void RealEstateManager::saveToFile(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    for (const auto &obj : objects) {
        file << "\"" << obj.owner << "\" "
             << std::put_time(&obj.registrationDate, "%Y.%m.%d") << " "
             << obj.estimatedCost << " "
             << "\"" << obj.address << "\" "
             << obj.numberOfRooms << "\n";
    }
}*/

void RealEstateManager::addObject(const RealEstate &object) {
    objects.push_back(object);
}

void RealEstateManager::removeObject(size_t index) {
    if (index >= objects.size()) {
        throw std::out_of_range("Index out of range");
    }
    objects.erase(objects.begin() + index);
}

const std::vector<RealEstate>& RealEstateManager::getObjects() const {
    return objects;
}
