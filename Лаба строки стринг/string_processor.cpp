#include "string_processor.h"
#include <iostream>
#include <cctype>

bool isOnlyDigits(const std::string& word) {
    if (word.empty()) return false;

    for (char c : word) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

bool isOnlyLetters(const std::string& word) {
    if (word.empty()) return false;

    for (char c : word) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

std::string reverseString(const std::string& str) {
    return std::string(str.rbegin(), str.rend());
}

std::string addLeadingZeros(const std::string& str, int targetLength) {
    if (static_cast<int>(str.length()) >= targetLength) {
        return str;
    }
    return std::string(targetLength - str.length(), '0') + str;
}

std::string processString(const std::string& input) {
    if (input.empty()) {
        return "Ошибка: строка пуста!";
    }

    std::vector<std::string> words;
    std::vector<std::string> spaces;
    std::string result;

    size_t i = 0;
    size_t n = input.length();

    std::string initialSpaces;
    while (i < n && std::isspace(static_cast<unsigned char>(input[i]))) {
        initialSpaces += input[i];
        i++;
    }
    result += initialSpaces;
    while (i < n) {
        std::string word;
        while (i < n && !std::isspace(static_cast<unsigned char>(input[i]))) {
            word += input[i];
            i++;
        }

        if (!word.empty()) {
            words.push_back(word);
        }

        std::string space;
        while (i < n && std::isspace(static_cast<unsigned char>(input[i]))) {
            space += input[i];
            i++;
        }
        spaces.push_back(space);
    }

    if (words.empty()) {
        return "Ошибка: в строке нет слов!";
    }

    for (size_t j = 0; j < words.size(); j++) {
        std::string word = words[j];

        if (isOnlyDigits(word) && word.length() < 5) {
            result += addLeadingZeros(word, 5);
        }
        else if (isOnlyLetters(word)) {
            result += reverseString(word);
        }
        else {
            result += word;
        }

        if (j < spaces.size()) {
            result += spaces[j];
        }
    }

    return result;
}