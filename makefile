OPTION=-s

all:
	make -C src $@ $(OPTION)
	@echo --- finish $@ ---

test: all
	make -C test $@ $(OPTION)
	@echo --- finish $@ ---

clean:
	make -C src $@ $(OPTION)
	make -C test $@ $(OPTION)
	@echo --- finish $@ ---

