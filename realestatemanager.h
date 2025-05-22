#ifndef REALESTATEMANAGER_H
#define REALESTATEMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include "realestate.h"

class RealEstateManager {
public:
    // Загрузка объектов из файла
    void loadFromFile(const std::string &filename);

    // Сохранение объектов в файл
    void saveToFile(const std::string &filename) const;

    // Добавление объекта
    void addObject(const RealEstate &object);

    // Удаление объекта по индексу
    void removeObject(size_t index);

    // Получение списка объектов
    const std::vector<RealEstate>& getObjects() const;

private:
    std::vector<RealEstate> objects;
};

#endif // REALESTATEMANAGER_H
