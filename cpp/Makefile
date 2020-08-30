ROOT := ..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

RPATH += -Wl,-rpath=$(DEST)
# 开源工具包路径
LDDIR += -L$(DEST)

# 开源工具包
LDLIBS += -lusgcommon

INCLUDES += -I$(ROOT)/common/include


PROGS =	$(DEST)/usestock1 $(DEST)/usetime3 $(DEST)/usebrass2 $(DEST)/vegnews $(DEST)/stdmove $(DEST)/typecast

DEPENDENCES = $(patsubst %, %.d, $(PROGS)) 

LIBCOMMON=$(DEST)/libusgcommon.so

all:	$(LIBCOMMON) $(PROGS)

# class
$(DEST)/usestock1 : usestock1.c stock10.c

# class: overload member operator
$(DEST)/usetime3: usetime3.c mytime3.c

# class inheritance: polymorphic public inheritance
$(DEST)/usebrass2: usebrass2.c brass.c

# class: copy constructor, copy assigment
$(DEST)/vegnews:  string1.c

# class: copy constructors, move constructors, copy assignment operators, and move assignment operators
$(DEST)/stdmove: stdmove.c

$(DEST)/typecast: typecast.c

clean:
	rm -f $(PROGS) $(DEPENDENCES) $(TEMPFILES)

$(LIBCOMMON):
	@(cd $(ROOT)/common && $(MAKE))

-include $(DEPENDENCES)
include $(ROOT)/Make.common.inc

