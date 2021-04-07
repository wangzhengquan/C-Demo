# debug "make --just-print"
DIRS = common test network jsoncpp
TAR_NAME = C-Demo.tar.gz

all:
	@for i in $(DIRS); do \
		(cd $$i && echo ">>>>>> making $$i ..." && $(MAKE) ) || exit 1; \
	done

clean:
	@rm -f $(TEMPFILES)
	@for i in $(DIRS); do \
		(cd $$i && echo ">>>>>> cleaning $$i ..." && $(MAKE) clean) || exit 1; \
	done


tar:
	rm -f $(TAR_NAME)
	git archive --format tar.gz --output $(TAR_NAME) master