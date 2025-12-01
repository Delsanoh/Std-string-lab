#include <iostream>
#include <string>
#include "string_processor.h"

#include <windows.h>

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string input;

    std::cout << "Введите строку: ";
    std::getline(std::cin, input);

    std::string result = processString(input);

    std::cout << "Результат: '" << result << "'" << std::endl;

    return 0;
}