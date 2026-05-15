#include "logger.h"

#include <cstdio>

void Logger::Log(const char* category, const char* format, ...) {
  va_list args{};
  va_start(args, format);
  PrintWithCategory(kColorWhite, category, format, args);
  va_end(args);
}

void Logger::Info(const char* category, const char* format, ...) {
  va_list args{};
  va_start(args, format);
  PrintWithCategory(kColorCyan, category, format, args);
  va_end(args);
}

void Logger::Warn(const char* category, const char* format, ...) {
  va_list args{};
  va_start(args, format);
  PrintWithCategory(kColorYellow, category, format, args);
  va_end(args);
}

void Logger::Error(const char* category, const char* format, ...) {
  va_list args{};
  va_start(args, format);
  PrintWithCategory(kColorRed, category, format, args);
  va_end(args);
}

void Logger::Value(const char* category, const char* format, ...) {
  va_list args{};
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
  bool in_color = false;
  bool color_started = false;
  for (int i = 0; buffer[i] != '\0'; i++) {
    char chr = buffer[i];
    if (!in_color && chr == ':') {
      printf("%c", chr);
      in_color = true;
      color_started = false;
      continue;
    }
    if (in_color && chr == ',') {
      if (color_started) {
        printf("%s", kColorReset);
      }
      in_color = false;
      printf("%c", chr);
      continue;
    }
    if (in_color) {
      if (!color_started) {
        printf("%s", kColorGreen);
        color_started = true;
      }
      printf("%c", chr);
    } else {
      printf("%c", chr);
    }
  }

  if (color_started) {
    printf("%s", kColorReset);
  }
  printf("\n");
  fflush(stdout);
}

bool Logger::IsDigit(char chr) {
  return chr >= '0' && chr <= '9';
}
