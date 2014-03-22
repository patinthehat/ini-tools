#include <string.h>

#define APP_VERSION "1.1"
#define BUFFER_SIZE 1024


#define ARGS_VERSION_COUNT  4
#define ARGS_HELP_COUNT     2


  int arg_c;
  char * arg_v[255];
  char * THIS_APP_FILENAME;

#if CONFIG_H == 0
  #define CONFIG_H 1

  char* const ARGS_VERSION[ARGS_VERSION_COUNT]  = {"-V", "-v", "--version", "--vers"};
  char* const ARGS_HELP[ARGS_HELP_COUNT]        = {"-h", "--help"};

  char* const DEFAULT_VALUE = "";

#endif
