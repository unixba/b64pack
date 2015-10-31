# Makefile for b64pack source and documentation

all:
	make -C src
	make -C doc

install:
	make -C src install
	make -C doc install

clean:
	make -C src clean
	make -C doc clean

.PHONY: all install clean
