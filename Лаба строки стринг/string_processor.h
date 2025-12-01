#ifndef STRING_PROCESSOR_H
#define STRING_PROCESSOR_H

#include <string>
#include <vector>

bool isOnlyDigits(const std::string& word);
bool isOnlyLetters(const std::string& word);
std::string reverseString(const std::string& str);
std::string addLeadingZeros(const std::string& str, int targetLength);
std::string processString(const std::string& input);

#endif 