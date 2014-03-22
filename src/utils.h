

  int file_exist (char *filename);

  int file_readable(char *filename);

  int file_writable(char *filename);

  int show_error(char *msg);

  int check_arg(char * argv[], int argn, char * value);

  int exit_return_value_success(int value, int successValue);

  int exit_return_value_failure(int value, int failureValue);

  int exit_return_value(int value, int successValue, int failureValue, int defaultValue);

  int is_bool_str_true(char *str);

  int is_bool_str_false(char *str);
