# vim: tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab

THISPROJECT="ini-tools"
THISDATE=`date`

INIREAD="ini-read"
INIWRITE="ini-write"

all: init iniread iniwrite
#	@make git-getdescription
#	@make git-setdescription
	@echo "\n* Compiled all targets for $(THISPROJECT) project."
	@exit 0
	
iniread: init src/ini-read.c
	@gcc -O3 -o build/$(INIREAD) src/$(INIREAD).c src/utils.c src/minIni.c
	@strip build/$(INIREAD)
	@echo "* Build finished: '$(INIREAD)'"
	@exit 0

iniwrite: init src/ini-write.c
	@gcc -O3 -o build/$(INIWRITE) src/utils.c src/minIni.c src/$(INIWRITE).c
	@strip build/$(INIWRITE)
	@echo "* Build finished: '$(INIWRITE)'"
	@exit 0

#gitgetdescription: init src/git-getdescription.c
#	@gcc -O3 -o build/git-getdescription src/utils.c src/git-getdescription.c
#	@strip build/git-getdescription
#	@echo "* Build finished: git-getdescription\n"
##  @exit 0
#	@exit 0
  
#git-getdescription: gitgetdescription
##	@make gitgetdescription

#git-setdescription: gitsetdescription
#

init:
	@echo "//automatically generated by make" > src/build-date.h
	@echo " " >> src/build-date.h
	@echo "#define BUILD_DATE \"$(THISDATE)\"" >> src/build-date.h
	@exit 0

clean: 
	@if [ -f build/$(INIREAD) ]; then  rm "build/$(INIREAD)"; echo "* Removed $(INIREAD)"; fi
	@if [ -f build/$(INIWRITE) ]; then  rm "build/$(INIWRITE)"; echo "* Removed $(INIWRITE)"; fi
#	@if [ -f build/git-getdescription ]; then rm build/git-getdescription; echo "removed git-getdescription"; fi
	@echo "\n* Cleaned all built files."
	@exit 0



#.PHONY: test help


