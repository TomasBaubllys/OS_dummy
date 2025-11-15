#include "../include/io.h"

bool line_ready() {
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    timeval tv = {0, 0};   // non-blocking
    int ret = select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv);
    return (ret > 0 && FD_ISSET(STDIN_FILENO, &fds));
}