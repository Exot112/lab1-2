#include <iostream>
#include <string>

bool isValidDate(const std::string& date) {
    int day, month, year;

    int result = sscanf(date.c_str(), "%2d.%2d.%4d", &day, &month, &year);
/*
    if (result != 3) {
        return false;
    }
/*
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0) {
        return false;
    }
*/
    return true;
}

int calcdate(const std::string& date)
{
    int sum = 0;
    for (char ch : date){
        if (isdigit(ch)){
            sum += ch - '0';
        }
    }
    return sum;
}

int main() {
    std::string date;
    std::cout << "Введите дате в формате дд.мм.гггг: ";
    std::cin >> date;

    if (isValidDate(date)) {
        int result = calcdate(date);
        std::cout << "\nСумма цифр: " << result << std::endl;
    } else {
        std::cout << "\nОшибка: дата введена некорректно." << std::endl;
    }

    return 0;
}
