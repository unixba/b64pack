# Makefile for b64pack documentation

MAN    = b64pack.1
GZMAN  = b64pack.1.gz
PREFIX = /usr/local

$(GZMAN): $(MAN)
	gzip -c $< >$@

install: $(GZMAN)
	install -m 644 $(GZMAN) $(PREFIX)/share/man/man1

clean:
	rm -f $(GZMAN)

.PHONY: clean
