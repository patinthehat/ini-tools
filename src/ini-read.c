#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "build-date.h"
#include "utils.h"
#include "minIni.h"


#define APP_TITLE "ini-read"

int show_usage (char *THIS_FILE_NAME) {
    //show the actual name of this file for usage info, even if it was changed from the default
    printf("Usage: %s [-b|--bool] section keyname filename\n  --bool reads a boolean and returns an int.\n", THIS_FILE_NAME);
    return -1;
}


//TODO add arg validation and error if not valid/not enough args

int main (int argc, char *argv[]) {
  char databuf[BUFFER_SIZE];


  long n;
  int nn;
  char *section, *name, *inifn;

  char* const THIS_FILE_NAME = strrchr(argv[0], '/') ? strrchr(argv[0], '/') + 1 : argv[0];
  char* const THIS_FILE_EXT = strrchr(THIS_FILE_NAME, '.') ? strrchr(THIS_FILE_NAME, '.') : THIS_FILE_NAME;

  if (argc <= 1)
    return show_usage(THIS_FILE_NAME);

  if (argc == 2 && (strncmp(argv[1], "-V", 2)==0 || strncmp(argv[1], "--version", 9) == 0)) {
    printf("%s v%s %s\n", APP_TITLE, APP_VERSION, BUILD_DATE);
    return 0;
  }

  if (argc >= 2 && (strncmp(argv[1], "-b", 2)==0 || strncmp(argv[1], "--bool", 6) == 0)) {
    section = argv[2];
    name = argv[3];
    inifn = argv[4];
    n = ini_gets(section, name, "", databuf, sizeof(databuf), inifn);

    //default value
    nn = 0;
    sprintf(databuf,"%d", nn);

    if (strcasecmp(databuf, "true")==0 || strcasecmp(databuf, "1")==0 ||
        strcasecmp(databuf, "yes")==0 || strcasecmp(databuf, "on")==0) {
      nn = 1;
      sprintf(databuf,"%d", nn);
    }

    if (strcasecmp(databuf, "false")==0 || strcasecmp(databuf, "0")==0 ||
        strcasecmp(databuf, "no")==0 || strcasecmp(databuf, "off")==0) {
      nn = 0;
      sprintf(databuf,"%d", nn);
    }

  } else {
    //default mode, return string value
    section = argv[1];
    name = argv[2];
    inifn = argv[3];

    n = ini_gets(section, name, "", databuf, sizeof(databuf), inifn);
  }

  printf("%s", databuf);

  return 0;
}
