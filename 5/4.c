//
// Created by finallie on 9/28/20.
//

#include <fcntl.h>
#include "tlpi_hdr.h"

int mydup(int fd) {
    return fcntl(fd, F_DUPFD, 0);
}

int mydup2(int fd, int fd2) {
    if (fd == fd2) {
        if (fcntl(fd, F_GETFL) == -1) {
            errno = EBADF;
            return -1;
        }
        return fd;
    } else {
        close(fd2);
        return fcntl(fd, F_DUPFD, fd2);
    }
}

int main() {
}