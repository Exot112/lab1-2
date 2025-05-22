#include "realestate.h"
#include <stdexcept>
#include <regex>
#include <sstream>
#include <iomanip>
#include "logger.h"

void RealEstate::parse(const std::string &description) {
    // Регулярное выражение для парсинга строки \"([^\"]+)\" - текст в ""; \\s+ - n-e кол-во пробелов;
    std::regex re("\"([^\\\"]+)\"\\s+(\\d{4})\\.(\\d{2})\\.(\\d{2})\\s+(\\d+)\\s+\"([^\\\"]+)\"\\s+(\\d+)$");
    std::smatch match;

    // Совпадение регулярного выражения с описанием
    if (!std::regex_match(description, match, re)) {
        try {
        throw std::invalid_argument("Invalid format");
        }
        catch (const std::exception &e) {
            log << "Ошибка в строке при добавлении элемента:" << " (" << e.what() << ")\n";
        }
    }

    // Извлечение данных из совпадений
    owner = match[1].str();
    registrationDate.tm_year = std::stoi(match[2].str()) - 1900; // Год смещается на 1900
    registrationDate.tm_mon = std::stoi(match[3].str()) - 1;    // Месяц смещается на 1
    registrationDate.tm_mday = std::stoi(match[4].str());
    estimatedCost = std::stoi(match[5].str());
    address = match[6].str();
    numberOfRooms = std::stoi(match[7].str());
}
