#define CONFIG_H 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "build-date.h"
#include "globals.h"
#include "config.h"
#include "utils.h"
#include "minIni.h"

#define APP_TITLE   APP_TITLE_INI_WRITE


int show_usage (char *THIS_FILE_NAME) {
    printf(
        "* Usage: %s [-v|--version|-h|--help|--delete-(key|section)] section keyname value filename\n" \
        "",
           THIS_FILE_NAME);
    return EXIT_FAILURE;
}

int show_help () {
  printf("%s v%s --\n", APP_TITLE, INI_TOOLS_VERSION);
  show_usage(THIS_APP_FILENAME);
  printf(
      "* ======\n" \
      "* -v|--version : shows version information\n" \
      "* -h|--help : shows this help information\n" \
      "* --delete-key : passing this will delete the specified key regardless of value specified. \n" \
      "* --delete-section : passing this will delete the specified section regardless of key/value specified.\n" \
      "\n" \
      "Writes value to section.keyname in the specified ini file.\n" \
      "%s",
      "");
  return EXIT_SUCCESS;
}



int main (int argc, char *argv[]) {
  char databuf[BUFFER_SIZE];
  char *section, *name, *value, *inifn;
  long nWriteSuccess = 0;
  int ret, firstArgIndex = 1;
  int bFlagDeleteSection = FALSE, bFlagDeleteKey = FALSE;

  application_init(argc, argv, arg_c, arg_v, &databuf, BUFFER_SIZE);

  if (argc <= 1) {
    show_error(STR_ERR_NOT_ENOUGH_ARGS);
    return show_usage(THIS_APP_FILENAME);
  }


  if (argc == 2) {
    if (check_arg_flag(1, FLAG_VERSION))
      return show_version(APP_TITLE, INI_TOOLS_VERSION);
    if (check_arg_flag(1, FLAG_HELP))
      return show_help();
  }

  if (check_arg(argv,1,"--delete-section") || check_arg(argv,1,"--delete-key")) {
    if (check_arg(argv,1,"--delete-key")) {
      bFlagDeleteKey = TRUE;
    } else {
      bFlagDeleteSection = TRUE;
    }
    firstArgIndex++;
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
  if (strcmp(inifn,"-")==0)
    inifn = "/dev/stdout";  //TODO modify minIni to support reading from stdin and using stdin data for writing

  if (file_exist(inifn) && !file_writable(inifn))
    return show_error_fmt(STR_ERR_FMT_FILE_NOT_WRITABLE, basename(inifn));

  if (!valid_section_name(section))
    return show_error(STR_ERR_INVALID_SECTION_NAME);
  if (!valid_key_name(name))
    return show_error(STR_ERR_INVALID_KEY_NAME);

  if (bFlagDeleteKey) {
    value = NULL; //passing NULL to ini_puts() deletes the key
  }

  if (bFlagDeleteSection) {
    name = NULL;  //passing NULL to ini_puts() deletes the entire section
    value = NULL; //set to NULL for good measure even though it will be deleted anyway
  }

  nWriteSuccess = ini_puts(section, name, value, inifn);

  ret = exit_return_value_failure(nWriteSuccess, 0);
  return ret;
}
