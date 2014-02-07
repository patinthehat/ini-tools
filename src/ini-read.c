#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <errno.h>
//#include <sys/stat.h>
#include "config.h"
#include "build-date.h"
#include "utils.h"
#include "minIni.h"

#define APP_TITLE "ini-read"

int main (int argc, char *argv[]) {
  char databuf[255];
  long n;
  char *section, *name, *inifn;

  if (argc == 2 && (strncmp(argv[1], "-V", 2)==0 || strncmp(argv[1], "--version", 9) == 0)) {
    printf("%s v%s %s\n", APP_TITLE, APP_VERSION, BUILD_DATE);
    return 0;
  }

  section = argv[1];
  name = argv[2];
  inifn = argv[3];

  n = ini_gets(section, name, "defval", databuf, sizeof(databuf), inifn);
  printf("%s", databuf);

  return 0;
}
