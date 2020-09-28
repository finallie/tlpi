//
// Created by finallie on 9/28/20.
//

//tee

#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[]) {
    int opt;
    Boolean a = FALSE;
    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
            case 'a':
                a = TRUE;
                break;
            default:
                usageErr("%s [-a] file", argv[0]);
                break;
        }
    }
    if (optind != argc - 1)
        usageErr("%s [-a] file\n", argv[0]);

    int flag = O_WRONLY | O_CREAT | (a ? O_APPEND : O_TRUNC);
    int fd = open(argv[argc - 1], flag, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IWOTH | S_IROTH);
    if (fd == -1)
        errExit("open");

    int n;
    char buf[BUFSIZ];
    while ((n = read(STDIN_FILENO, buf, BUFSIZ)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n || write(fd, buf, n) != n)
            errExit("write");
    }
    if (n == -1)
        errExit("read");
}