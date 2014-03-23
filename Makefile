# vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab

#get the project name from the project directory
THISPROJECT=`basename $(realpath .)`
THISDATE=`date +"%Y-%b-%d %R"`
REV_NUM=`git log --format=%cr | wc -l`
GITREV=`git log -1 --format=%h HEAD`

INIREAD=ini-read
INIWRITE=ini-write
INSTDIR=$(HOME)/scripts

#gcccpuopt-generated settings
MORE_CC_FLAGS=' '
GCCOPTS=-march=native -mfpmath=sse -msse3 -Wno-deprecated-declarations
GCCOPTLEVEL=3
STRIPBINS=1

#=============================================================
COLOR_WHITE=\033[1;37m
COLOR_RED=\033[1;31m
COLOR_GREEN=\033[1;32m
COLOR_BLUE=\033[1;34m
COLOR_DIMBLUE=\033[0;34m
COLOR_TEAL=\033[1;36m
COLOR_YELLOW=\033[1;33m
COLOR_END=\033[m
INIREAD_COLOR=$(COLOR_WHITE)$(INIREAD)$(COLOR_END)
INIWRITE_COLOR=$(COLOR_WHITE)$(INIWRITE)$(COLOR_END)
#=============================================================

all: minIni init $(INIREAD) $(INIWRITE)
	@echo "\n$(COLOR_YELLOW)*$(COLOR_END) Compiled all targets for $(THISPROJECT) project, revision $(COLOR_BLUE)$(GITREV)$(COLOR_END) (#$(REV_NUM))."
	@exit 0
	
$(INIREAD): init src/ini-read.c
	@gcc $(GCCOPTS) -O$(GCCOPTLEVEL) -o build/$@ src/$@.c src/utils.c src/minIni.o
	@if [ $(STRIPBINS) -eq 1 ]; then strip build/$@; echo "* Stripped binary '$(COLOR_WHITE)build/$@$(COLOR_END)'"; fi
	@buildmsg "Build finished" blue $@
	@exit 0

$(INIWRITE): init src/ini-write.c
	@gcc $(GCCOPTS) -O$(GCCOPTLEVEL) -o build/$@ src/$@.c src/utils.c src/minIni.o
	@if [ $(STRIPBINS) -eq 1 ]; then strip build/$@; echo "* Stripped binary '$(COLOR_WHITE)build/$@$(COLOR_END)'"; fi
	@buildmsg "Build finished" blue $@
	@exit 0

init:	minIni
	@if [ ! -d build ]; then mkdir build; fi
	@echo "//automatically generated by make" > src/build-date.h
	@echo " " >> src/build-date.h
	@echo "#define BUILD_DATE \"$(THISDATE)\"" >> src/build-date.h
	@buildmsg "Build finished" blue "automatically generated files"
	@exit 0

minIni: src/minIni.c
	@gcc -O1 -c src/minIni.c -o src/minIni.o > /dev/null
	@buildmsg "Build finished" blue "library - minIni"
	@exit 0

clean: 
	@if [ -f build/$(INIREAD) ]; then  rm "build/$(INIREAD)"; echo "* Removed $(INIREAD)"; fi
	@if [ -f build/$(INIWRITE) ]; then  rm "build/$(INIWRITE)"; echo "* Removed $(INIWRITE)"; fi
	@if [ -f src/minIni.o ]; then rm "src/minIni.o"; echo "* Removed src/minIni.o"; fi
	@echo "\n$(COLOR_YELLOW)*$(COLOR_END) Cleaned all built files in build/."
	@exit 0

install:
	@if [ -f build/$(INIREAD) ]; then cp "build/$(INIREAD)" "$(INSTDIR)/$(INIREAD)" && echo "* Installed $(COLOR_WHITE)$(INIREAD)$(COLOR_END) to $(INSTDIR)"; fi
	@if [ -f build/$(INIWRITE) ]; then cp "build/$(INIWRITE)" "$(INSTDIR)/$(INIWRITE)" && echo "* Installed $(COLOR_WHITE)$(INIWRITE)$(COLOR_END) to $(INSTDIR)"; fi
	@echo "\n$(COLOR_YELLOW)*$(COLOR_END) Finished installing files."
	@exit 0

#.PHONY: test help

