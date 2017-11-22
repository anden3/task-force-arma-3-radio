#pragma once

#include "common.hpp"

#ifdef _WIN32
    #include <Windows.h>
#endif

class pipe_handler {
public:
    pipe_handler();
    ~pipe_handler();

    bool getData(std::string& output, std::chrono::milliseconds timeout);
    bool sendData(const std::string& data) const;
    bool sendData(const char* data, size_t length) const;
    bool isConnected() { return m_isConnected; }

private:
#ifdef _WIN32
    void openPipe();

    HANDLE pipe = INVALID_HANDLE_VALUE;
    HANDLE waitForDataEvent = INVALID_HANDLE_VALUE;
#else
    void openPipes();

    int readPipe = -1;
    int writePipe = -1;
#endif

    bool m_isConnected;
};

