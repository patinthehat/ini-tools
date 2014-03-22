#define CONFIG_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "build-date.h"
#include "globals.h"
#include "config.h"
#include "utils.h"
#include "minIni.h"


#define APP_TITLE   APP_TITLE_INI_READ

int show_usage (char *THIS_FILE_NAME) {
    //show the actual name of this file for usage info, even if it was changed from the default
    printf(
        "* Usage: %s [(-v|--version)|(-h|--help)|(-b|--bool|--boolean)|(-d|--dump)] section keyname filename\n" \
        "",
        THIS_FILE_NAME);
    return EXIT_FAILURE;
}

int show_help(char *THIS_FILE_NAME) {
  printf("%s v%s --\n", APP_TITLE, INI_TOOLS_VERSION);
  show_usage(THIS_FILE_NAME);
  printf(
        "* ======\n" \
        "* -v|--version : shows version information\n" \
        "* -h|--help : shows this help information\n" \
        "* -d|--dump [file]: dumps the contents of given ini file.\n" \
        "* -b|--bool|--boolean reads a boolean string and returns an int(0 or 1). " \
        "1 == TRUE, 0 == FALSE \n" \
        "* valid boolean strings are 'true','false','yes','no','on','off','1','0'\n" \
        "%s", "");
  return EXIT_SUCCESS;
}


static mTCHAR * lastSection = "";

int browsecb(const mTCHAR *Section, const mTCHAR *Key, const mTCHAR *Value, const void *UserData) {
  if (lastSection == Section) {

  }
  if (lastSection=="" || strcasecmp((char*)Section, (char*)lastSection)!=0 ) {
    printf("[%s]\n",Section);
  }
  printf("%s=%s\n", Key, Value);

  lastSection = strdup(Section);
  return 1;
}


int main (int argc, char *argv[]) {
  char databuf[BUFFER_SIZE];
  char *section, *name, *inifn;
  long n;
  int nn;
  int bFlagBool = FALSE, bFlagDump = FALSE;
  int firstArgIndex = 1;
  char* const DEFAULT_VALUE = "";

  memset(databuf, 0, sizeof(databuf));

  application_init(argc, argv, arg_c, arg_v);



  if (argc <= 1) {
    show_error(STR_ERR_NOT_ENOUGH_ARGS);
    return show_usage( THIS_APP_FILENAME );
  }

  bFlagBool = (check_arg_flag_bool(1) ? TRUE : FALSE);
  bFlagDump = (check_arg_flag(1, FLAG_DUMP) ? TRUE : FALSE);

  if (argc == 2) {
    if (bFlagBool==TRUE)
      return show_error(STR_ERR_NOT_ENOUGH_ARGS);
    if (bFlagDump)
      return show_error(STR_ERR_NO_FILE_NAME);

    if (check_arg_flag(1, FLAG_VERSION))
      return show_version(APP_TITLE, INI_TOOLS_VERSION);

    if (check_arg_flag(1, FLAG_HELP))
      return show_help( THIS_APP_FILENAME );
  }


  firstArgIndex = 1;  //first arg is index 1,
  if (bFlagBool || bFlagDump)
    firstArgIndex++;  //unless -b|-d is passed

  //--- start dump file processing ---
  if (bFlagDump) {
    inifn   = argv[firstArgIndex];
    if (!file_exist(inifn))
      return show_error(STR_ERR_FILE_NOT_FOUND);
    if (!file_readable(inifn))
      return show_error_f1(STR_ERR_FMT_FILE_NOT_READABLE, basename(inifn));

    ini_browse(browsecb, NULL, inifn);
    return EXIT_SUCCESS;
  }
  //--- end dump file processing ---


  // --- start error checking ---
  if (argc <= firstArgIndex)
    return show_error(STR_ERR_NO_SECTION_NAME);
  if (argc <= firstArgIndex+1)
    return show_error(STR_ERR_NO_KEY_NAME);
  if (argc <= firstArgIndex+2)
    return show_error(STR_ERR_NO_FILE_NAME);
  // --- end error checking ---

  section = argv[firstArgIndex+0];
  name    = argv[firstArgIndex+1];
  inifn   = argv[firstArgIndex+2];

  // -- start sanity checking --
  if (!file_exist(inifn))
    return show_error(STR_ERR_FILE_NOT_FOUND);

  if (!file_readable(inifn))
    return show_error_f1(STR_ERR_FMT_FILE_NOT_READABLE, basename(inifn));

  if (!valid_section_name(section))
    return show_error(STR_ERR_INVALID_SECTION_NAME);

  if (!valid_key_name(name))
    return show_error(STR_ERR_INVALID_KEY_NAME);
  // -- end sanity checking --

  n = ini_gets(section, name, DEFAULT_VALUE, databuf, sizeof(databuf), inifn);

  if (bFlagBool) {
    nn = FALSE; //default value
    if (is_bool_str_true(databuf))
      nn = TRUE;
    if (is_bool_str_false(databuf))
      nn = FALSE;
    sprintf(databuf,"%d", nn);
  }

  printf("%s", databuf);
  return EXIT_SUCCESS;
}
