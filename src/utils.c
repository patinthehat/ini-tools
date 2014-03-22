
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include "config.h"
#include "build-date.h"


void application_init(int argc, char*argv[], int argc_global, char*argv_global[]) {
  int n;

  argc_global = argc;
  for(n = 0; n < argc; n++)
   argv_global[n] = argv[n];

  THIS_APP_FILENAME = (char*)(strrchr(arg_v[0], '/') ? strrchr(arg_v[0], '/') + 1 : arg_v[0]);

}


int file_exist (char *filename) {
  struct stat   buffer;
  return (stat (filename, &buffer) == 0);
}

int file_readable(char *filename) {
  if (access(filename, R_OK) == 0)
    return 1;
  return 0;
}

int file_writable(char *filename) {
  if (access(filename, W_OK) == 0)
    return 1;
  return 0;
}

int show_version(char * APPLICATION_TITLE, char * APPLICATION_VERSION) {
  printf("%s v%s %s\n", APPLICATION_TITLE, APPLICATION_VERSION, BUILD_DATE);
  return EXIT_SUCCESS;
}

int show_error(char *msg) {
  printf("* Error: %s\n", msg);
  return EXIT_FAILURE;
}

int show_error_f1(char *msgfmt, void *arg) {
  printf(msgfmt, arg);
  return EXIT_FAILURE;
}

int check_arg(char * argv[], int argn, char * value) {
  size_t slen = strlen(value);
  if (strncmp(argv[argn], value, slen )==0)
    return 1;
  return 0;
}

int check_arg_char_array(char *argv[], int index, char * arr[]) {
  int ret, i;
  for(i = 0; i < sizeof(arr); i++)
    ret = ret || check_arg(argv, index, arr[i]);
  return ret;
}

int check_arg_char_array_const(char *argv[], int index, char * const arr[]) {
  int ret, i;
  for(i = 0; i < sizeof(arr); i++)
    ret = ret || check_arg(argv, index, arr[i]);
  return ret;
}

int check_arg_flag_version(int index) {
  return check_arg_char_array_const(arg_v, index, ARGS_VERSION);
}

int check_arg_flag_help(int index) {
  return check_arg_char_array_const(arg_v, index, ARGS_HELP);
}


int exit_return_value_success(int value, int successValue) {
  if (value == successValue)
    return EXIT_SUCCESS;
  return EXIT_FAILURE;
}

int exit_return_value_failure(int value, int failureValue) {
  if (value == failureValue)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int exit_return_value(int value, int successValue, int failureValue, int defaultValue) {
  if (value == failureValue)
    return EXIT_FAILURE;
  if (value == successValue)
    return EXIT_SUCCESS;
  return defaultValue;
}


/**
 * checks a string as a boolean value == true
 * @arg char* str string to check
 * returns true if str in [true,1,yes,on]
 */
int is_bool_str_true(char *str) {
  if (strcasecmp(str, "true")==0 || strcasecmp(str, "1")==0 ||
      strcasecmp(str, "yes")==0 || strcasecmp(str, "on")==0)
    return 1;
  return 0;
}

/**
 * checks a string as a boolean value == false
 * @arg char* str string to check
 * returns true if str in [false,0,-1,no,off]
 */
int is_bool_str_false(char *str) {
  if (strcasecmp(str, "false")==0 || strcasecmp(str, "0")==0 || strcasecmp(str, "-1")==0 ||
      strcasecmp(str, "no")==0 || strcasecmp(str, "off")==0)
    return 1;
  return 0;
}

char * get_app_name() { //char * argv[]) {
  char* const THIS_FILENAME = (char*)basename( (char*)arg_v[0] );//strrchr(argv[0], '/') ? strrchr(argv[0], '/') + 1 : argv[0];
  //char* const THIS_FILEEXT = strrchr(THIS_FILENAME, '.') ? strrchr(THIS_FILENAME, '.') : THIS_FILENAME;
  return (char*)THIS_FILENAME;
}

int valid_section_name(char*sectionName) {
  if (sectionName == NULL || strlen(sectionName) == 0 || !sectionName)
    return 0;
  return 1;
}

int valid_key_name(char*keyName) {
  if (keyName == NULL || strlen(keyName) == 0 || !keyName)
    return 0;
  return 1;
}
