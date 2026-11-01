#include "utils/data.h"

#include <errno.h>
#include <stddef.h>
#include <unistd.h>

static int read_all(int fd, void *buffer, size_t count) {
  unsigned char *ptr = buffer;

  while (count > 0) {
    ssize_t n = read(fd, ptr, count);

    if (n < 0) {
      if (errno == EINTR)
        continue;

      return -1;
    }

    if (n == 0)
      return -1; // Unexpected EOF

    ptr += n;
    count -= (size_t)n;
  }

  return 0;
}

static int write_all(int fd, const void *buffer, size_t count) {
  const unsigned char *ptr = buffer;

  while (count > 0) {
    ssize_t n = write(fd, ptr, count);

    if (n < 0) {
      if (errno == EINTR)
        continue;

      return -1;
    }

    if (n == 0)
      return -1;

    ptr += n;
    count -= (size_t)n;
  }

  return 0;
}

int utils_read(int fd, float *sample) {
  return read_all(fd, sample, sizeof(*sample));
}

int utils_write(int fd, const float *sample) {
  return write_all(fd, sample, sizeof(*sample));
}
