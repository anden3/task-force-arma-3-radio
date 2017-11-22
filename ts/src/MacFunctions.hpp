#pragma once

#ifdef __APPLE__

#include <cstddef>

#define MB_OK 0x00000000L
#define MAX_PATH 260
#define _TRUNCATE (static_cast<size_t>(-1))

bool canUseSSE2();
int MessageBoxA(int ownerWindow, const char* message, const char* title, unsigned int flags);
void __debugbreak();
int _snprintf_s(char* buffer, size_t buflen, size_t count, const char* format, ...);

#endif
