#define CONFIG_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>

#include "globals.h"
#include "config.h"
#include "build-date.h"

#include "utils.h"
#include "minIni.h"

#define APP_TITLE   APP_TITLE_INI_WRITE


int show_usage (char *THIS_FILE_NAME) {
    printf(
        "* Usage: %s section keyname value filename\n" \
        "",
           THIS_FILE_NAME);
    return EXIT_FAILURE;
}

int show_help () {
  printf("%s v%s --\n", APP_TITLE, INI_TOOLS_VERSION);
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
  int firstArgIndex = 1;

  application_init(argc, argv, arg_c, arg_v);

  if (argc <= 1) {
    show_error(STR_ERR_NOT_ENOUGH_ARGS);
    return show_usage(THIS_APP_FILENAME);
  }

  if (argc == 2) {
    if (check_arg_flag_version(1))
      return show_version(APP_TITLE, INI_TOOLS_VERSION);
    if (check_arg_flag_help(1))
      return show_help();
  }

  if (argc <= firstArgIndex+1)
    return show_error(STR_ERR_NO_KEY_NAME);
  if (argc <= firstArgIndex+2)
    return show_error(STR_ERR_NO_VALUE);
  if (argc <= firstArgIndex+3)
    return show_error(STR_ERR_NO_FILE_NAME);

  section = argv[firstArgIndex];
  name    = argv[firstArgIndex+1];
  value   = argv[firstArgIndex+2];
  inifn   = argv[firstArgIndex+3];

  if (!file_writable(inifn))
    return show_error_f1(STR_ERR_FMT_FILE_NOT_WRITABLE, basename(inifn));

  if (!valid_section_name(section))
    return show_error(STR_ERR_INVALID_SECTION_NAME);
  if (!valid_key_name(name))
    return show_error(STR_ERR_INVALID_KEY_NAME);

  n = ini_puts(section, name, value, inifn);

  ret = exit_return_value_failure(n, 0);
  return ret;
}
