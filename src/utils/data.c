#include "utils/data.h"

#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
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

float *utils_resample(const float *input, size_t N, double fs_old,
                      double fs_new, size_t *N_out) {
  if (!input || !N_out || N == 0 || fs_old <= 0 || fs_new <= 0)
    return NULL;

  *N_out = (size_t)ceil(N * fs_new / fs_old);

  float *output = malloc(*N_out * sizeof(*output));

  if (!output)
    return NULL;

  for (size_t m = 0; m < *N_out; m++) {

    // Corresponding position in original signal
    double position = m * fs_old / fs_new;

    size_t n = (size_t)position;

    // Handle end of input
    if (n >= N - 1) {
      output[m] = input[N - 1];
      continue;
    }

    double alpha = position - n;

    output[m] = (float)((1.0 - alpha) * input[n] + alpha * input[n + 1]);
  }

  return output;
}
