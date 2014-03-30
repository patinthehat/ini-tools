#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>

#include "globals.h"

#ifndef APPLICATION_H
#define APPLICATION_H 1


typedef struct
{
    char const * name;
    char const * version;
    char const * package;

    int errorState;

  struct
  {
    char const * filename;
    char const * section;
    char const * keyname;
  } settings;
    int arg_c;
    char const * arg_v[];
} application_t;

typedef application_t application;
typedef application * application_ptr;

#define INITAPP(a, aptr, TITLE, VERS, PKGNAME, argc, argv) \
  aptr = &a; \
  a.name=TITLE; a.version = VERS; a.package = PKGNAME; \
  a.errorState = FALSE; \
  a.arg_c = argc; \
  int n = 0; for(; n<argc; n++) a.arg_v[n] = argv[n]; //copy argv to app.arg_v


#endif
