
#define APP_VERSION   "1.3"
#define BUFFER_SIZE   1024

#define INI_TOOLS_VERSION   APP_VERSION

#define ARGS_VERSION_COUNT  4
#define ARGS_HELP_COUNT     2
#define ARGS_BOOL_COUNT     3
#define ARGS_DUMP_COUNT     2

enum application_flag {
  FLAG_VERSION,
  FLAG_HELP,
  FLAG_BOOL,
  FLAG_DUMP
};

int arg_c;
char * arg_v[255];
char * THIS_APP_FILENAME;

#if CONFIG_H == 0
  #undef CONFIG_H
  #define CONFIG_H 1

  char* ARGS_VERSION[ARGS_VERSION_COUNT]  = {"-V", "-v", "--version", "--vers"};
  char* ARGS_HELP[ARGS_HELP_COUNT]        = {"-h", "--help"};
  char* ARGS_BOOL[ARGS_BOOL_COUNT]        = {"-b", "--bool", "--boolean"};
  char* ARGS_DUMP[ARGS_DUMP_COUNT]        = {"-d", "--dump"};

  char* const DEFAULT_VALUE = "";

#endif
