## ini-tools
  - command line tools to read and write ini files easily and quickly (i.e. in scripts).

----


### Requirements

  + `buildmsg` - The `ini-tools` `Makefile` uses the `buildmsg` script from _[quantum-utils](https://github.com/patinthehat/quantum-utils)_.  
      In order to build this project, you must have `buildmsg` in your $PATH. 


  + [minIni](https://code.google.com/p/minini/) 1.2b is used to process the ini files.  It is included in the `src/` directory.

---

### Building

once `buildmsg` is installed, run any of the following to build.

  + `make all`
  + `nake ini-read`
  + `nake ini-write`

The `Makefile` will also automatically generate `src/build-date.h` which adds the build date to the `--version` output.


