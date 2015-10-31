# Makefile - b64pack Makefile
# 
# Copyright (C) 2015 Kenan Kalajdzic <kenan@unix.ba>
#
# This file is part of b64pack.
#
# B64pack is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# B64pack is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with b64pack.  If not, see <http://www.gnu.org/licenses/>.

CC     = gcc
CFLAGS = -O2
OUT    = b64pack
HDR    = b64pack.h
OBJ    = b64pack.o compress.o error.o io.o
PREFIX = /usr/local

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $<

install: $(OUT)
	install -m 755 -s $< $(PREFIX)/bin

clean:
	rm -f $(OBJ) $(OUT)

.PHONY: clean
