# debug "make --just-print"
DIRS = common test network

all:
	@for i in $(DIRS); do \
		(cd $$i && echo ">>>>>> making $$i ..." && $(MAKE) ) || exit 1; \
	done

clean:
	@rm -f $(TEMPFILES)
	@for i in $(DIRS); do \
		(cd $$i && echo ">>>>>> cleaning $$i ..." && $(MAKE) clean) || exit 1; \
	done
