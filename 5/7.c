//
// Created by finallie on 9/29/20.
//

#include <sys/uio.h>
#include "tlpi_hdr.h"

size_t count_iovec(const struct iovec *vec, int count) {
    size_t sum = 0;
    while (count--)
        sum += (vec++)->iov_len;
    return sum;
}

ssize_t myreadv(int fd, const struct iovec *vec, int count) {
    size_t bufsiz = count_iovec(vec, count);
    void *buf = malloc(bufsiz);
    if (buf == NULL) return -1;

    ssize_t n = read(fd, buf, bufsiz);
    if (n == -1) {
        free(buf);
        return -1;
    }

    for (size_t i = 0; count--; i += min(vec->iov_len, n - i), ++vec) {
        memcpy(vec->iov_base, buf + i, min(vec->iov_len, n - i));
    }

    free(buf);
    return n;
}

ssize_t mywritev(int fd, const struct iovec *vec, int count) {
    size_t bufsiz = count_iovec(vec, count);
    void *buf = malloc(bufsiz);
    if (buf == NULL) {
        return -1;
    }

    for (void *p = buf; count--; p += vec->iov_len, ++vec)
        memcpy(p, vec->iov_base, vec->iov_len);

    ssize_t n = writev(fd, buf, bufsiz);
    free(buf);
    return n;
}

int main() {

}