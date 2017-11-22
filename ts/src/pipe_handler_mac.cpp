#ifdef __APPLE__

#include "pipe_handler.hpp"
#include "profilers.hpp"
#include <thread>

#include <sys/ioctl.h>
#include <sys/stat.h>

#include <fcntl.h>

pipe_handler::pipe_handler() {}

pipe_handler::~pipe_handler() {
    close(readPipe);
    close(writePipe);
}

extern volatile bool pipeConnected;

bool pipe_handler::getData(std::string& output, std::chrono::milliseconds timeout) {
    output.resize(4096);

    for (int it = 0; it < timeout.count(); it++) {
        if (readPipe == -1) {
            openPipes();
        }

        int numBytesRead = 0;
        int numBytesAvail = 0;

        if (ioctl(readPipe, FIONREAD, &numBytesAvail) == 0) {
            if (numBytesAvail > 0) {
                numBytesRead = read(readPipe, &output[0], 4096);

                if (numBytesRead >= 0) {
                    m_isConnected = true;
                    output.resize(numBytesRead);
                    return true;
                }
                else {
                    m_isConnected = false;
                    openPipes();
                    std::this_thread::sleep_for(50us);
                    return false;
                }
            }
        }
        else {
            m_isConnected = false;
            openPipes();
            std::this_thread::sleep_for(50us);
            return false;
        }

        std::this_thread::sleep_for(1ms);
    }

    return false;
}


bool pipe_handler::sendData(const std::string& data) const {
    return sendData(data.c_str(), data.length());
}


bool pipe_handler::sendData(const char* data, size_t length) const {
    return write(writePipe, data, length) >= 0;
}

void pipe_handler::openPipes() {
    if (readPipe != -1) {
        close(readPipe);
        readPipe = -1;
    }

    if (writePipe != -1) {
        close(writePipe);
        writePipe = -1;
    }

    mkfifo(PIPE_NAME, 0666);
    readPipe = open(PIPE_NAME, O_RDONLY);
    writePipe = open(PIPE_NAME, O_WRONLY);
}

#endif
