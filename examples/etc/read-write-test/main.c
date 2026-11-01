#include "utils/data.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {

  const char *path = "../../../../data/read-write_test.txt";
  int fd = open(path, O_RDWR | O_CREAT);

  if (fd == -1) {
    perror("open");
    return 1;
  }

  float value = 100.00;
  utils_read(fd, &value);

  close(fd);

  return 0;
}
