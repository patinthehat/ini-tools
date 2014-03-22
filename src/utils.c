
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
//#include <sys/stat.h>

#include "globals.h"
#include "config.h"
#include "build-date.h"

/**
 * copies main(argc,argv) to global vars, initializes THIS_APP_FILENAME global var
 * @param argc from main()
 * @param argv from main()
 * @param argc_global global var
 * @param argv_global global var
 */
void application_init(int argc, char*argv[], int argc_global, char*argv_global[]) {
  int n;

  argc_global = argc;
  for(n = 0; n < argc; n++)
   argv_global[n] = argv[n];

  THIS_APP_FILENAME = (char*)(strrchr(arg_v[0], '/') ? strrchr(arg_v[0], '/') + 1 : arg_v[0]);
}

/**
 * checks if a file exists.
 * @param char* filename
 * @return true if given file exists, otherwise false.
 */
int file_exist (char *filename) {
//  struct stat   buffer;
//  return (stat (filename, &buffer) == 0);
  if (access(filename, F_OK) == 0)
    return TRUE;
  return FALSE;
}

/**
 * checks if specified file is readable.
 * @param char* filename
 * @return int TRUE if readable, otherwise FALSE
 */
int file_readable(char *filename) {
  if (access(filename, R_OK) == 0)
    return TRUE;
  return FALSE;
}

/**
 * checks if specified file is writable.
 * @param char* filename
 * @return int TRUE if writable, otherwise FALSE
 */
int file_writable(char *filename) {
  if (access(filename, W_OK) == 0)
    return TRUE;
  return FALSE;
}

/**
 * displays version information
 * @param APPLICATION_TITLE name of the application
 * @param APPLICATION_VERSION version string to display
 * @return int returns EXIT_SUCCESS
 */
int show_version(char * APPLICATION_TITLE, char * APPLICATION_VERSION) {
  printf("%s v%s %s\n", APPLICATION_TITLE, APPLICATION_VERSION, BUILD_DATE);
  return EXIT_SUCCESS;
}

/**
 * displays an error message and returns EXIT_FAILURE.
 * @param msg message to display
 * @return int EXIT_FAILURE
 */
int show_error(char *msg) {
  fprintf(stderr, "%s%s\n", STR_ERROR_PREFIX, msg);
  return EXIT_FAILURE;
}

/**
 * displays an error message formatted with one argument and returns EXIT_FAILURE.
 * @param msgfmt
 * @param arg
 * @return int EXIT_FAILURE
 */
int show_error_f1(char *msgfmt, void *arg) {
  char * buf;
  buf = malloc(strlen(msgfmt)+(sizeof(char)*11));
  sprintf(buf, "%s%s\n", STR_ERROR_PREFIX, msgfmt);
  fprintf(stderr, buf, arg);
  free(buf);
  return EXIT_FAILURE;
}

/**
 * checks an argv index against value
 * @param argv argv from main
 * @param argn index to check
 * @param value value to compare
 * @return int TRUE if argv[index] == value, otherwise FALSE
 */
int check_arg(char * argv[], int argn, char * value) {
  size_t slen = strlen(value);
  if (strncmp(argv[argn], value, slen )==0)
    return TRUE;
  return FALSE;
}

/**
 * checks argv[index] against an array of values
 * @param argv
 * @param index
 * @param arr array of values to check for
 * @param size size of arr
 * @return int TRUE if argv[index] is one of arr[], otherwise FALSE
 */
int check_arg_char_array(char *argv[], int index, char * arr[], int size) {
  int ret, i;
  for(i = 0; i < size; i++)
    ret = ret || check_arg(argv, index, arr[i]);
  return ret;
}

/**
 * checks argv[index] against an array of const values
 * @param argv
 * @param index
 * @param arr array of values to check for
 * @param size size of arr
 * @return int TRUE if argv[index] is one of arr[], otherwise FALSE
 */
int check_arg_char_array_const(char *argv[], int index, char * const arr[], int size) {
  int ret, i;
  for(i = 0; i < size; i++)
    ret = ret || check_arg(argv, index, arr[i]);
  return ret;
}

/**
 * checks argv[index] for the given flag
 * @param index argv index to check
 * @param flag flag to check for
 * @return int TRUE|FALSE
 */
int check_arg_flag(int index, enum application_flag flag) {
  switch(flag) {
    case FLAG_VERSION:
      return check_arg_flag_version(index);
      break;
    case FLAG_HELP:
      return check_arg_flag_help(index);
      break;
    case FLAG_BOOL:
      return check_arg_flag_bool(index);
      break;
    case FLAG_DUMP:
      return check_arg_char_array(arg_v, 1, ARGS_DUMP, ARGS_DUMP_COUNT);
      break;
    default:
      return FALSE;
  }
}

int check_arg_flag_version(int index) {
  return check_arg_char_array(arg_v, index, ARGS_VERSION, ARGS_VERSION_COUNT);
}

int check_arg_flag_help(int index) {
  return check_arg_char_array(arg_v, index, ARGS_HELP, ARGS_HELP_COUNT);
}

int check_arg_flag_bool(int index) {
  return check_arg_char_array(arg_v, index, ARGS_BOOL, ARGS_BOOL_COUNT);
}

/**
 * checks if value==successValue and returns EXIT_SUCCESS, otherwise EXIT_FAILURE
 * @param value
 * @param successValue
 * @return int EXIT_SUCCESS if value==successValue, otherwise EXIT_FAILURE
 */
int exit_return_value_success(int value, int successValue) {
  if (value == successValue)
    return EXIT_SUCCESS;
  return EXIT_FAILURE;
}

/**
 * checks if value==failureValue and returns EXIT_FAILURE, otherwise EXIT_SUCCESS
 * @param value
 * @param failureValue
 * @return int EXIT_FAILURE if value==failureValue, otherwise EXIT_SUCCESS
 */
int exit_return_value_failure(int value, int failureValue) {
  if (value == failureValue)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

/**
 * checks value against other values to return EXIT_SUCCESS/FAILURE
 * @param value
 * @param successValue
 * @param failureValue
 * @param defaultValue
 * @return int EXIT_SUCCESS if value==successValue,EXIT_FAILURE if value==failureValue, otherwise defaultValue
 */
int exit_return_value(int value, int successValue, int failureValue, int defaultValue) {
  if (value == failureValue)
    return EXIT_FAILURE;
  if (value == successValue)
    return EXIT_SUCCESS;
  return defaultValue;
}

/**
 * checks a string as a boolean value == true
 * @param str string to check
 * returns true if str in [true,1,yes,on]
 */
int is_bool_str_true(char *str) {
  if (strcasecmp(str, "true")==0 || strcasecmp(str, "1")==0 ||
      strcasecmp(str, "yes")==0 || strcasecmp(str, "on")==0)
    return TRUE;
  return FALSE;
}

/**
 * checks a string as a boolean value == false
 * @param str string to check
 * returns true if str in [false,0,-1,no,off]
 */
int is_bool_str_false(char *str) {
  if (strcasecmp(str, "false")==0 || strcasecmp(str, "0")==0 || strcasecmp(str, "-1")==0 ||
      strcasecmp(str, "no")==0 || strcasecmp(str, "off")==0)
    return TRUE;
  return FALSE;
}

char * get_app_name() { //char * argv[]) {
  char* const THIS_FILENAME = (char*)basename( (char*)arg_v[0] );//strrchr(argv[0], '/') ? strrchr(argv[0], '/') + 1 : argv[0];
  //char* const THIS_FILEEXT = strrchr(THIS_FILENAME, '.') ? strrchr(THIS_FILENAME, '.') : THIS_FILENAME;
  return (char*)THIS_FILENAME;
}

/**
 * checks validity of an ini section name
 * @param sectionName
 * @return int TRUE if sectionName is valid, FALSE otherwise
 */
int valid_section_name(char*sectionName) {
  if (sectionName == NULL || strlen(sectionName) == 0 || !sectionName)
    return FALSE;
  return TRUE;
}

/**
 * checks validity of an ini key name
 * @param keyName
 * @return int TRUE if keyName is valid, FALSE otherwise
 */
int valid_key_name(char*keyName) {
  if (keyName == NULL || strlen(keyName) == 0 || !keyName)
    return FALSE;
  return TRUE;
}
