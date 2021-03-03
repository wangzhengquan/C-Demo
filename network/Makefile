ROOT := ..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

#RPATH += -Wl,-rpath=$(DEST)

# 开源工具包路径
LDDIR += -L$(DEST)

# 开源工具包
LDLIBS += -lusgcommon

INCLUDES += -I$(ROOT)/common/include


PROGS =	$(DEST)/broadcast_sender $(DEST)/broadcast_receiver \
				$(DEST)/MulticastReceiver $(DEST)/MulticastSender \
				$(DEST)/echoserver_epoll  $(DEST)/echoserver_poll $(DEST)/echoclient


DEPENDENCES = $(patsubst %, %.d, $(PROGS)) 

LIBCOMMON=$(DEST)/libusgcommon.a

build:	$(LIBCOMMON) $(PROGS)
# build:	$(PROGS)

symbal: build
	$(NM) -n $(DEST)/test_logger > $(DEST)/test_logger.sym

clean:
	rm -f $(PROGS) $(DEPENDENCES) $(TEMPFILES)

$(LIBCOMMON):
	@(cd $(ROOT)/common && $(MAKE))

-include $(DEPENDENCES)
include $(ROOT)/Make.common.inc

