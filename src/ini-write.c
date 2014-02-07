#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <errno.h>
//#include <sys/stat.h>
#include "config.h"
#include "build-date.h"
#include "utils.h"
#include "minIni.h"

#define APP_TITLE "ini-write"

int main (int argc, char *argv[]) {
  char databuf[255];
  long n;
  int ret;
  char *section, *name, *value, *inifn;

  if (argc == 2 && (strncmp(argv[1], "-V", 2)==0 || strncmp(argv[1], "--version", 9) == 0)) {
    printf("%s v%s %s\n", APP_TITLE, APP_VERSION, BUILD_DATE);
    return 0;
  }

  section = argv[1];
  name = argv[2];
  value = argv[3];
  inifn = argv[4];

  n = ini_puts(section, name, value, inifn);
  ret = 0;
  if (n == 0) 
    ret = -1;
  //printf("%s", databuf);
  return ret;
}
