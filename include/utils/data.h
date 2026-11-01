#ifndef UTILS_DATA_H
#define UTILS_DATA_H

#include <stddef.h>

int utils_read(int fd, float *sample);
int utils_write(int fd, const float *sample);
float *utils_resample(const float *input, size_t N, double fs_old,
                      double fs_new, size_t *N_out);

#endif
