#include <fcntl.h>
#include "tlpi_hdr.h"

int main() {
    int fd = open("test.txt", O_WRONLY | O_APPEND);
    lseek(fd, 0, SEEK_SET);
    write(fd, "123\n", 4);
    printf("%ld", lseek(fd, 0, SEEK_CUR));
}
