

# help - The default goal
.PHONY: help
help:
	@make --print-data-base --question no-such-target | \
	grep -v -e '^no-such-target' -e '^makefile' |       \
	awk '/^[^.%][-A-Za-z0-9_]*:/                        \
	    { print substr($$1, 1, length($$1)-1) }' |      \
	sort |                                              \
	pr --omit-pagination --width=80 --columns=4         \



$(DEST)/%.d: %.c
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$;                      \
	sed 's,\($*\)\.o[ :]*,$(DEST)/\1 $(DEST)/\1.o $@ : ,g' < $@.$$$$ > $@;     \
	rm -f $@.$$$$

$(DEST)/%.o: %.c
	$(CC) ${CPPFLAGS} $(CFLAGS) -c $(filter %.c, $^) -o $@


${DEST}/%:	%.o
	$(CC) $(filter %.o, $^) -o $@ $(LDFLAGS) $(LDLIBS)

${DEST}/%:	%.c
	$(CC) ${CPPFLAGS} $(CFLAGS) $(filter %.c, $^) -o $@ $(LDFLAGS) $(LDLIBS)


# $(LIBCOMMON):
#	(cd $(ROOT)/common && $(MAKE))
