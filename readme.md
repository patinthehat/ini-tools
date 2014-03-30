## ini-tools [![Build Status](https://travis-ci.org/patinthehat/ini-tools.svg?branch=master)](https://travis-ci.org/patinthehat/ini-tools)
  - command line tools to read and write ini files easily and quickly (i.e. in scripts).

----


### Requirements

  + `buildmsg` - The `ini-tools` `Makefile` uses the `buildmsg` script from _[quantum-utils](https://github.com/patinthehat/quantum-utils)_.  
      In order to build this project, you must have `buildmsg` in your $PATH. 


  + [minIni](https://code.google.com/p/minini/) 1.2b is used to process the ini files.  It is included in the `src/` directory.

---

### Building

first, make sure `buildmsg` is installed, or remove the `buildmsg` lines from the `Makefile`.

  1. + `make minIni` to build the minIni library - _builds minIni.o_

  1. + run any of:
    + `make all`
    + `nake ini-read`
    + `nake ini-write`

---

 + The `Makefile` will automatically generate `src/build-date.h` when building any ini-tools project, which adds the build date to the `--version` output.

 + By default, the compiled binaries will be output to `build/`.

 + `make install` moves the compiled binaries to `HOME/scripts`, by default.  Either add this path to your `$PATH` or modify the Makefile to install to another location.

---

### Examples
  _test.ini_

```
[Last]
key1=yes
newkey2=myvalue
key3=test value
[First]
newkey3=myvalue
```

---


  + `ini-read Last key3 test.ini`
  + `ini-read --dump test.ini`
  + `ini-read --dump test.ini Last`

` `


  + `ini-write Last key4 "new key" test.ini`


---

