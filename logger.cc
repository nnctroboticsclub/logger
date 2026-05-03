#include "logger.h"

#include <cerrno>

void Logger::Log(const char* category, const char* format, ...) {
  va_list args;
  va_start(args, format);
  PrintWithCategory(kColorWhite, category, format, args);
  va_end(args);
}

void Logger::Info(const char* category, const char* format, ...) {
  va_list args;
  va_start(args, format);
  PrintWithCategory(kColorCyan, category, format, args);
  va_end(args);
}

void Logger::Warn(const char* category, const char* format, ...) {
  va_list args;
  va_start(args, format);
  PrintWithCategory(kColorYellow, category, format, args);
  va_end(args);
}

void Logger::Error(const char* category, const char* format, ...) {
  va_list args;
  va_start(args, format);
  PrintWithCategory(kColorRed, category, format, args);
  va_end(args);
}

void Logger::Value(const char* category, const char* format, ...) {
  va_list args;
  va_start(args, format);
  PrintValueWithColoredNumbers(category, format, args);
  va_end(args);
}

void Logger::PrintWithCategory(const char* color, const char* category,
                               const char* format, va_list args) {
  printf("%s[%s] > ", color, category);
  vprintf(format, args);
  printf("%s\n", kColorReset);
  fflush(stdout);
}

void Logger::PrintValueWithColoredNumbers(const char* category,
                                          const char* format, va_list args) {
  char buffer[256];
  vsnprintf(buffer, sizeof(buffer), format, args);
  printf("[%s] > ", category);
  bool in_number = false;
  for (int i = 0; buffer[i] != '\0'; i++) {
    char chr = buffer[i];
    bool is_digit_or_hex = IsDigit(chr) || (chr >= 'a' && chr <= 'f') ||
                           (chr >= 'A' && chr <= 'F') || chr == 'x' ||
                           chr == 'X';
    if (!in_number &&
        (IsDigit(chr) ||
         (chr == '0' && (buffer[i + 1] == 'x' || buffer[i + 1] == 'X')))) {
      printf("%s", kColorGreen);
      in_number = true;
    }
    if (in_number && !is_digit_or_hex) {
      printf("%s", kColorReset);
      in_number = false;
    }
    printf("%c", chr);
  }

  if (in_number) {
    printf("%s", kColorReset);
  }
  printf("\n");
  fflush(stdout);
}

bool Logger::IsDigit(char chr) {
  return chr >= '0' && chr <= '9';
}
