#include "pch.h"
#include "../Лаба строки стринг/string_processor.cpp"


TEST(StringProcessorTest, IsOnlyDigitsTest) {
    EXPECT_TRUE(isOnlyDigits("12345"));
    EXPECT_TRUE(isOnlyDigits("0"));
    EXPECT_TRUE(isOnlyDigits("999"));

    EXPECT_FALSE(isOnlyDigits(""));
    EXPECT_FALSE(isOnlyDigits("12a34"));
    EXPECT_FALSE(isOnlyDigits("abc"));
    EXPECT_FALSE(isOnlyDigits("12.34"));
    EXPECT_FALSE(isOnlyDigits(" 123"));
    EXPECT_FALSE(isOnlyDigits("123 "));
}

TEST(StringProcessorTest, IsOnlyLettersTest) {
    EXPECT_TRUE(isOnlyLetters("hello"));
    EXPECT_TRUE(isOnlyLetters("WORLD"));
    EXPECT_TRUE(isOnlyLetters("Test"));

    EXPECT_FALSE(isOnlyLetters(""));
    EXPECT_FALSE(isOnlyLetters("hello123"));
    EXPECT_FALSE(isOnlyLetters("123"));
    EXPECT_FALSE(isOnlyLetters("hello world"));
    EXPECT_FALSE(isOnlyLetters("test!"));
}

TEST(StringProcessorTest, ReverseStringTest) {
    EXPECT_EQ(reverseString("hello"), "olleh");
    EXPECT_EQ(reverseString("12345"), "54321");
    EXPECT_EQ(reverseString("a"), "a");
    EXPECT_EQ(reverseString(""), "");
    EXPECT_EQ(reverseString("test string"), "gnirts tset");
}

TEST(StringProcessorTest, AddLeadingZerosTest) {
    EXPECT_EQ(addLeadingZeros("123", 5), "00123");
    EXPECT_EQ(addLeadingZeros("12", 5), "00012");
    EXPECT_EQ(addLeadingZeros("1", 5), "00001");
    EXPECT_EQ(addLeadingZeros("12345", 5), "12345");
    EXPECT_EQ(addLeadingZeros("123456", 5), "123456"); // Длина уже больше
    EXPECT_EQ(addLeadingZeros("", 5), "00000");
}

TEST(StringProcessorTest, ProcessShortDigitWords) {
    EXPECT_EQ(processString("123 45 6"), "00123 00045 00006");
    EXPECT_EQ(processString("test 12 abc"), "tset 00012 cba");
    EXPECT_EQ(processString("9999 10000"), "09999 10000"); // 9999 -> 09999, 10000 без изменений
}

TEST(StringProcessorTest, ProcessLetterWords) {
    EXPECT_EQ(processString("hello world"), "olleh dlrow");
    EXPECT_EQ(processString("TEST"), "TSET");
    EXPECT_EQ(processString("a b c"), "a b c"); // Односимвольные слова остаются
}

TEST(StringProcessorTest, ProcessMixedWords) {
    EXPECT_EQ(processString("hello123 test456"), "hello123 test456");
    EXPECT_EQ(processString("123abc 45def"), "123abc 45def");
    EXPECT_EQ(processString("test123!"), "test123!");
}

TEST(StringProcessorTest, PreserveSpaces) {
    EXPECT_EQ(processString("  hello  world  "), "  olleh  dlrow  ");
    EXPECT_EQ(processString("123  45"), "00123  00045");
    EXPECT_EQ(processString("\ttest\n123\t"), "\ttset\n00123\t");
}

TEST(StringProcessorTest, EdgeCases) {
    // Пустая строка
    EXPECT_EQ(processString(""), "Ошибка: строка пуста!");

    // Только пробелы
    EXPECT_EQ(processString("   "), "Ошибка: в строке нет слов!");

    // Одно слово
    EXPECT_EQ(processString("hello"), "olleh");
    EXPECT_EQ(processString("123"), "00123");
    EXPECT_EQ(processString("12345"), "12345"); // Ровно 5 цифр
    EXPECT_EQ(processString("123456"), "123456"); // Больше 5 цифр

    // Очень длинное цифровое слово
    EXPECT_EQ(processString("1234567890"), "1234567890");
}

TEST(StringProcessorTest, ComplexTest) {
    std::string input = "  123 test 4567 hello89 world 99999   ";
    std::string expected = "  00123 tset 04567 hello89 dlrow 99999   ";
    EXPECT_EQ(processString(input), expected);
}
TEST(StringProcessorTest, RussianLettersTest) {
    // Тест с русскими буквами
    std::string input = "привет мир";
    std::string result = processString(input);
    // Проверяем, что результат не содержит ошибок
    EXPECT_NE(result, "Ошибка: строка пуста!");
    EXPECT_NE(result, "Ошибка: в строке нет слов!");
    EXPECT_TRUE(result.length() > 0);
}

TEST(StringProcessorTest, DifferentWhitespaceTest) {
    std::string input = "hello\tworld\n123\t\t456";
    std::string result = processString(input);
    // Проверяем, что слова обработаны правильно
    EXPECT_TRUE(result.find("olleh") != std::string::npos);  // hello -> olleh
    EXPECT_TRUE(result.find("dlrow") != std::string::npos);  // world -> dlrow
    EXPECT_TRUE(result.find("00123") != std::string::npos);  // 123 -> 00123
    EXPECT_TRUE(result.find("00456") != std::string::npos);  // 456 -> 00456
}