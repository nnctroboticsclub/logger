#pragma once

#include <cstdarg>

class Logger {
 public:
  static void Log(const char* category, const char* format, ...);
  static void Info(const char* category, const char* format, ...);
  static void Warn(const char* category, const char* format, ...);
  static void Error(const char* category, const char* format, ...);
  static void Value(const char* category, const char* format, ...);

 private:
  static constexpr const char* kColorReset = "\033[0m";
  static constexpr const char* kColorRed = "\033[31m";
  static constexpr const char* kColorGreen = "\033[32m";
  static constexpr const char* kColorYellow = "\033[33m";
  static constexpr const char* kColorBlue = "\033[34m";
  static constexpr const char* kColorMagenta = "\033[35m";
  static constexpr const char* kColorCyan = "\033[36m";
  static constexpr const char* kColorWhite = "\033[37m";

  static void PrintWithCategory(const char* color, const char* category,
                                const char* format, va_list args);
  static void PrintValueWithColoredNumbers(const char* category,
                                           const char* format, va_list args);
  static bool IsDigit(char chr);
};
