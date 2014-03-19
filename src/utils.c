
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <errno.h>
#include <sys/stat.h>


int file_exist (char *filename) {
  struct stat   buffer;
  return (stat (filename, &buffer) == 0);
}


int show_error(char *msg) {
  printf("* Error: %s\n", msg);
  return -1;
}
