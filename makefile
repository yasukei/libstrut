
all:
	make -C src $@
	@echo --- finish $@ ---

test: all
	make -C test $@
	@echo --- finish $@ ---

clean:
	make -C src $@
	make -C test $@
	@echo --- finish $@ ---

