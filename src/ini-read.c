

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define CONFIG_H 1
#include "config.h"
#include "build-date.h"

#include "utils.h"
#include "minIni.h"


#define APP_TITLE "ini-read"

int show_usage (char *THIS_FILE_NAME) {
    //show the actual name of this file for usage info, even if it was changed from the default
    printf(
        "* Usage: %s [-b|--bool] section keyname filename\n" \
        "",
        THIS_FILE_NAME);
    return EXIT_FAILURE;
}

int show_help(char *THIS_FILE_NAME) {
  printf("%s v%s --\n", APP_TITLE, APP_VERSION);
  show_usage(THIS_FILE_NAME);
  printf(
        "* ======\n" \
        "* --bool reads a boolean and returns an int.\n" \
        "* valid boolean strings are 'true','false','yes','no','on','off','1','0'\n" \
        "%s",
        ""
  );

  return EXIT_SUCCESS;
}



int main (int argc, char *argv[]) {
  char databuf[BUFFER_SIZE];
  char *section, *name, *inifn;
  long n;
  int nn;
  char* const DEFAULT_VALUE = "";

  memset(databuf, 0, sizeof(databuf));

  application_init(argc, argv, arg_c, arg_v);

  if (argc <= 1)
    return show_usage( THIS_APP_FILENAME );

  if (argc == 2) {
    if (check_arg(argv, 1, "-b") || check_arg(argv, 1, "--bool"))
      return show_error("Not enough arguments.");

    if (check_arg_flag_version(1))
      return show_version(APP_TITLE, APP_VERSION);

    if (check_arg_flag_help(1))
      return show_help( THIS_APP_FILENAME );
  }


  if (argc >= 2 && (check_arg(argv, 1, "-b") || check_arg(argv,1,"--bool"))) {

    if (argc <= 2)
      return show_error("No section name specified.");
    if (argc <= 3)
      return show_error("No key name specified.");
    if (argc <= 4)
      return show_error("No filename specified.");

    section = argv[2];
    name    = argv[3];
    inifn   = argv[4];

    if (!file_exist(inifn))
      return show_error("file not found.");
    if (!file_readable(inifn))
      return show_error_f1("File '%s' is not readable.\n", basename(inifn));
    if (!valid_section_name(section))
      return show_error("Invalid section name.");
    if (!valid_key_name(name))
      return show_error("Invalid key name.");

    n = ini_gets(section, name, DEFAULT_VALUE, databuf, sizeof(databuf), inifn);

    //default value
    nn = 0;
    if (is_bool_str_true(databuf))
      nn = 1;
    if (is_bool_str_false(databuf))
      nn = 0;
    sprintf(databuf,"%d", nn);
  } else {
    //default mode, return string value

    if (argc <= 1)
      return show_error("No section name specified.");
    if (argc <= 2)
      return show_error("No key name specified.");
    if (argc <= 3)
      return show_error("No filename specified.");

    section = argv[1];
    name    = argv[2];
    inifn   = argv[3];

    if (!file_exist(inifn))
      return show_error("file not found.");
    if (!file_readable(inifn))
      return show_error_f1("File '%s' is not readable.\n", basename(inifn));
    if (!valid_section_name(section))
      return show_error("Invalid section name.");
    if (!valid_key_name(name))
      return show_error("Invalid key name.");

    n = ini_gets(section, name, DEFAULT_VALUE, databuf, sizeof(databuf), inifn);
  }

  printf("%s", databuf);

  return EXIT_SUCCESS;
}
