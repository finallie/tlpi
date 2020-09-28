//
// Created by finallie on 9/28/20.
//

//cp
#include "tlpi_hdr.h"
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 3)
        usageErr("%s file_src file_dest");
    int fin = open(argv[1], O_RDONLY);
    if (fin == -1)
        errExit("open src");
    int fout = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IROTH | S_IWOTH | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (fout == -1)
        errExit("open dest");

    int n;
    char buf[BUFSIZ];
    while ((n = read(fin, buf, BUFSIZ)) > 0) {
        for (int i = 0, j = 0; i < n;) {
            while (j < n && buf[j])++j;
            if (j - i && write(fout, buf, j - i) != j - i)
                errExit("write");
            i = j;
            while (j < n && !buf[j]) ++j;
            if (j - i && lseek(fout, j - i, SEEK_CUR) == -1)
                errExit("lseek");
            i = j;
        }
    }
    if (n == -1)
        errExit("read");
    if (close(fin) == -1 || close(fout) == -1)
        errExit("close");
}