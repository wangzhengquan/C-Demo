ROOT := ..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

RPATH += -Wl,-rpath=$(DEST):$(ROOT)/lib/jsoncpp
# 开源工具包路径
LDDIR += -L$(DEST) -L$(ROOT)/lib/jsoncpp

# 开源工具包
LDLIBS += -lusgcommon -ljsoncpp

INCLUDES += -I$(ROOT)/common/include -I$(ROOT)/include


PROGS =	$(DEST)/test_json

DEPENDENCES = $(patsubst %, %.d, $(PROGS)) 

LIBCOMMON=$(DEST)/libusgcommon.so

all:	$(LIBCOMMON) $(PROGS)

clean:
	rm -f $(PROGS) $(DEPENDENCES) $(TEMPFILES) *.json

$(LIBCOMMON):
	@(cd $(ROOT)/common && $(MAKE))

-include $(DEPENDENCES)
include $(ROOT)/Make.common.inc



