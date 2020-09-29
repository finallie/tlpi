//
// Created by finallie on 9/28/20.
//

//atomic_append

#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
    if ((argc != 3 && argc != 4) || (argc == 4 && strcmp(argv[3], "x") != 0) || strcmp(argv[1], "--help") == 0)
        usageErr("%s file number [x]\n", argv[0]);

    long num = getLong(argv[2], GN_ANY_BASE | GN_NONNEG, NULL);
    int fd = open(argv[1], O_WRONLY | O_CREAT | (argc == 3 ? O_APPEND : 0), S_IWUSR | S_IRUSR);
    if (fd == -1)
        errExit("open");

    while (num-- > 0) {
        if (argc == 4) {
            if (lseek(fd, 0, SEEK_END) == -1)
                errExit("lseek");
        }
        if (write(fd, "a", 1) != 1)
            errExit("write");
    }

    if (close(fd) == -1) errExit("close");
    exit(EXIT_SUCCESS);
}