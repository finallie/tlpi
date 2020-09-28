#include "tlpi_hdr.h"
#include <fcntl.h>

int main() {
    int fd = open("test.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("open");
    lseek(fd, 0, SEEK_END);
    int n = write(fd, "abc123", 6);
    if (n == -1)
        errExit("write");
    if (close(fd) == -1)
        errExit("close");
}
