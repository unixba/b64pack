/*
 * io.c - input and output functions for b64pack
 * 
 * Copyright (C) 2015 Kenan Kalajdzic <kenan@unix.ba>
 *
 * This file is part of b64pack.
 *
 * B64pack is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * B64pack is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with b64pack.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

#include "b64pack.h"

size_t get_message(char **msg)
{
    char *buf;
    size_t buflen, msglen;

    buf = NULL;
    buflen = 0;
    msglen = 0;

    while (!feof(stdin)) {
        buflen += MSG_BLKSIZE;
        if ((buf = (char *) realloc(buf, buflen)) == NULL)
            err_sys("realloc");
        msglen += fread(&buf[msglen], 1, MSG_BLKSIZE, stdin);
        if (ferror(stdin))
            err_sys("fread");
    }

    if (msglen < MSG_MINLEN)
        err_out(ERROR_LENGTH);

    if ((*msg = (char *) realloc(buf, msglen * 4)) == NULL)
        err_sys("realloc");

    return msglen;
}

void put_message(const char *msg, size_t len)
{
    fwrite(msg, 1, len, stdout);
}
