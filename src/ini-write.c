#define CONFIG_H 1

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


int show_usage (char *THIS_FILE_NAME) {
    printf(
        "* Usage: %s section keyname value filename\n" \
        "",
           THIS_FILE_NAME);
    return EXIT_FAILURE;
}

int show_help () {
  printf("%s v%s --\n", APP_TITLE, APP_VERSION);
  show_usage(THIS_APP_FILENAME);
  printf(
      "* ======\n" \
      "\n" \
      "%s",
      "");
  return EXIT_SUCCESS;
}


int main (int argc, char *argv[]) {
  char databuf[BUFFER_SIZE];
  char *section, *name, *value, *inifn;
  long n;
  int ret;

  application_init(argc, argv, arg_c, arg_v);

  if (argc <= 1)
    return show_usage(THIS_APP_FILENAME);

  if (argc == 2) {
    if (check_arg_flag_version(1))
      return show_version(APP_TITLE, APP_VERSION);
    if (check_arg_flag_help(1))
      return show_help();
  }

  if (argc <= 2)
    return show_error("No key name specified.");

  if (argc <= 3)
    return show_error("No value specified.");

  if (argc <= 4)
    return show_error("No filename specified.");

  section = argv[1];
  name    = argv[2];
  value   = argv[3];
  inifn   = argv[4];

  if (!file_writable(inifn))
    return show_error_f1("File '%s' not writable.", basename(inifn));

  if (!valid_section_name(section))
    return show_error("Invalid section name.");

  if (!valid_key_name(name))
    return show_error("Invalid key name.");

  n = ini_puts(section, name, value, inifn);

  ret = exit_return_value_failure(n, 0);
  return ret;
}
