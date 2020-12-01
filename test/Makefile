ROOT := ..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

#RPATH += -Wl,-rpath=$(DEST)

# 开源工具包路径
LDDIR += -L$(DEST)

# 开源工具包
LDLIBS += -lusgcommon

INCLUDES += -I$(ROOT)/common/include


PROGS =	$(DEST)/test_file $(DEST)/test1 $(DEST)/test_strjoin

DEPENDENCES = $(patsubst %, %.d, $(PROGS)) 

LIBCOMMON=$(DEST)/libusgcommon.a

build:	$(LIBCOMMON) $(PROGS)
	cp config.txt $(DEST)/config.txt

symbal: build
	$(NM) -n $(DEST)/test_logger > $(DEST)/test_logger.sym

clean:
	rm -f $(PROGS) $(DEPENDENCES) $(TEMPFILES)

$(LIBCOMMON):
	@(cd $(ROOT)/common && $(MAKE))

-include $(DEPENDENCES)
include $(ROOT)/Make.common.inc

