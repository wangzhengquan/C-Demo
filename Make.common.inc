

# help - The default goal
.PHONY: help
help:
	@make --print-data-base --question no-such-target | \
	grep -v -e '^no-such-target' -e '^makefile' |       \
	awk '/^[^.%][-A-Za-z0-9_]*:/                        \
	    { print substr($$1, 1, length($$1)-1) }' |      \
	sort |                                              \
	pr --omit-pagination --width=80 --columns=4         \

include $(patsubst %.c, $(DEST)/%.d, $(SOURCES)) 

$(DEST)/%.d: %.c
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$;                      \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;     \
	rm -f $@.$$$$

$(DEST)/%.o: %.c
	$(CC) ${CPPFLAGS} $(CFLAGS) -c $^ -o $@


${DEST}/%:	%.c
	$(CC) ${CPPFLAGS} $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

# $(LIBCOMMON):
#	(cd $(ROOT)/common && $(MAKE))
