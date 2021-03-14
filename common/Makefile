#
# Makefile for common library.
#
ROOT := ..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

PREFIX = $(DEST)
LIBCOMMON = $(DEST)/libusgcommon.a
DLIBCOMMON = $(DEST)/libusgcommon.so

SOURCES := $(wildcard *.cpp ./**/*.cpp)
OBJS   = $(patsubst %.cpp, $(DEST)/%.o, $(SOURCES)) 
DEPENDENCES = $(patsubst %.cpp, $(DEST)/%.d, $(SOURCES)) 

# MYLIBS = $(LIBCOMMON) $(DLIBCOMMON)

ifeq ($(DEBUG),y)
  MYLIBS = $(LIBCOMMON)
else
  MYLIBS = $(LIBCOMMON) $(DLIBCOMMON)
endif

#PREFIX is environment variable, but if it is not set, then set default value
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

all: build
 

.PHONY: build
build: prebuild $(MYLIBS)

.PHONY: prebuild
prebuild:
	@test -d $(DEST) || mkdir $(DEST)

#static lib
$(LIBCOMMON): $(OBJS)
	@echo '>>>>>>' generating $@ ...
	@$(AR) rv $@ $?
	@$(RANLIB) $@

#dynamic lib
$(DLIBCOMMON): $(SOURCES)
	@echo '>>>>>>' generating $@ ...
	$(CC) -fPIC -shared $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $^ -o $@
	md5sum $(DLIBCOMMON) > $(DLIBCOMMON).md5
	# md5sum -c $(DLIBCOMMON).md5



# 使用方式： g++ test1.c  -lcommon
.PHONY: install
install: $(MYLIBS)
	@echo '>>>>>>' installing $^ ...
	install -d $(PREFIX)/lib/
	install -m 644 $^ $(PREFIX)/lib/
	install -d $(PREFIX)/include/usgcommon
	install -m 644 include/* $(PREFIX)/include/usgcommon

.PHONY: uninstall
uninstall:
	@echo '>>>>>>' uninstalling ...
	rm -rf $(PREFIX)/include/usgcommon
	rm -f $(PREFIX)/lib/libusgcommon.*


.PHONY: clean
clean:
	rm -f $(OBJS) $(MYLIBS) $(DEPENDENCES) $(TEMPFILES)


-include $(DEPENDENCES)
include $(ROOT)/Make.common.inc
