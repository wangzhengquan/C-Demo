ROOT := ..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

# RPATH += -Wl,-rpath=$(DEST)
# 开源工具包路径
LDDIR += -L$(DEST)

# 开源工具包
LDLIBS += -lusgcommon -lpthread

INCLUDES += -I$(ROOT)/common/include


PROGS =	$(DEST)/stock10_usage $(DEST)/mytime3_usage $(DEST)/brass_usage \
				$(DEST)/vegnews $(DEST)/stdmove $(DEST)/typecast \
				$(DEST)/container_usage  $(DEST)/shared_ptr_test \
				$(DEST)/binary_format  $(DEST)/mutable_usage \
				$(DEST)/allocator_demo $(DEST)/hash_table/extendible_hash_table

DEPENDENCES = $(patsubst %, %.d, $(PROGS)) 

LIBCOMMON=$(DEST)/libusgcommon.a

all:	$(LIBCOMMON) $(PROGS)

# extendible_hash_table
$(DEST)/hash_table/extendible_hash_table : hash_table/main.cpp hash_table/extendible_hash_table.cpp hash_table/extendible_hash_table.h
# class
$(DEST)/stock10_usage : stock10_usage.cpp stock10.cpp

# class: overload member operator
$(DEST)/mytime3_usage: mytime3_usage.cpp mytime3.cpp

# class inheritance: polymorphic public inheritance
$(DEST)/brass_usage: brass_usage.cpp brass.cpp

# class: copy constructor, copy assigment
$(DEST)/vegnews:  string1.cpp

# class: copy constructors, move constructors, copy assignment operators, and move assignment operators
$(DEST)/stdmove: stdmove.cpp

$(DEST)/typecast: typecast.cpp

clean:
	rm -f $(PROGS) $(DEPENDENCES) $(TEMPFILES)

$(LIBCOMMON):
	@(cd $(ROOT)/common && $(MAKE))

-include $(DEPENDENCES)
include $(ROOT)/Make.common.inc


