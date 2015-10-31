/*
 * b64pack.c - compress short text messages using base64 decoding
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
#include <string.h>

#include "b64pack.h"

int main(int argc, char *argv[])
{
    char *msg;
    size_t msglen;
    int operation;

    switch (argc) {
    case 1:
        operation = OP_COMPRESS;
        break;
    case 2:
        if (strcmp(argv[1], "-d") == 0) {
            operation = OP_DECOMPRESS;
            break;
        }
    default:
        err_use(argv[0]);
    }

    msglen = get_message(&msg);

    if (operation == OP_COMPRESS)
        b64pack_compress(msg, &msglen);
    else
        b64pack_decompress(msg, &msglen);

    put_message(msg, msglen);

    exit(EXIT_SUCCESS);
}
