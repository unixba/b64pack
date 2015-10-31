/*
 * compress.c - (de)compression functions for b64pack
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

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "b64pack.h"

static char *table1 = "@$_!\"#%&'()*+,-./:;<=>?\n";
static char *table2 = "[\\]^{|}~`\t";
static char *table3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                      "abcdefghijklmnopqrstuvwxyz"
                      "0123456789+/";

void b64pack_compress(char *msg, size_t *msglen)
{
    int i, j;
    char *p, *enc;

    if ((enc = (char *) malloc(*msglen * 4)) == NULL)
        err_sys("malloc");

    /*
     * Phase 1 - Encode
     */
    for (i = j = 0; i < *msglen; i++) {
        if (isalnum(msg[i]))
            enc[j++] = msg[i];
        else if (msg[i] == ' ') {
            if (j > 1 && islower(enc[j-1]) && enc[j-2] == '+')
                enc[j-1] = toupper(enc[j-1]);
            else
                enc[j++] = '/';
        } else if (msg[i] != '\0' && (p = strchr(table1, msg[i])) != NULL) {
            enc[j++] = '+';
            enc[j++] = 'a' + (p - table1);
        } else if (msg[i] != '\0' && (p = strchr(table2, msg[i])) != NULL) {
            enc[j++] = '+';
            enc[j++] = '+';
            enc[j++] = 'a' + (p - table2);
        } else
            err_out(ERROR_INPUT);
    }

    /* Pad message with spaces */
    while (j % 4 != 0)
        enc[j++] = '/';
    *msglen = j;

    /*
     * Phase 2 - Compress
     */
    for (i = j = 0; i < *msglen; i++) {
        if ((p = strchr(table3, enc[i++])) == NULL)
            err_out(ERROR_TRANS);
        msg[j] = (p - table3) << 2;
        if ((p = strchr(table3, enc[i++])) == NULL)
            err_out(ERROR_TRANS);
        msg[j++] |= (p - table3) >> 4;
        msg[j] = (p - table3) << 4;
        if ((p = strchr(table3, enc[i++])) == NULL)
            err_out(ERROR_TRANS);
        msg[j++] |= (p - table3) >> 2;
        msg[j] = (p - table3) << 6;
        if ((p = strchr(table3, enc[i])) == NULL)
            err_out(ERROR_TRANS);
        msg[j++] |= p - table3;
    }
    *msglen = j;
    free(enc);
}

void b64pack_decompress(char *msg, size_t *msglen)
{
    int i, j;
    char *dec;

    if ((dec = (char *) malloc(*msglen * 4)) == NULL)
        err_sys("malloc");

    /*
     * Phase 1 - Decompress
     */
    for (i = j = 0; i < *msglen; i += 3) {
        dec[j++] = table3 [ msg[i]   >> 2 & 0x3f ];
        dec[j++] = table3 [ msg[i]   << 4 & 0x3f | msg[i+1] >> 4 & 0xf ];
        dec[j++] = table3 [ msg[i+1] << 2 & 0x3f | msg[i+2] >> 6 & 0x3 ];
        dec[j++] = table3 [ msg[i+2]      & 0x3f ];
    }
    *msglen = j;

    /*
     * Phase 2 - Decode
     */
    for (i = j = 0; i < *msglen; i++) {
        if (dec[i] == '+') {
            if (++i >= *msglen)
                err_out(ERROR_INPUT);
            if (dec[i] == '+') {
                if (++i >= *msglen)
                    err_out(ERROR_INPUT);
                if (tolower(dec[i]) < 'a' || tolower(dec[i]) > 'j')
                    err_out(ERROR_INPUT);
                msg[j++] = table2[tolower(dec[i]) - 'a'];
            } else {
                if (tolower(dec[i]) < 'a' || tolower(dec[i]) > 'x')
                    err_out(ERROR_INPUT);
                msg[j++] = table1[tolower(dec[i]) - 'a'];
            }
            if (isupper(dec[i]))
                msg[j++] = ' ';
        } else if (dec[i] == '/')
            msg[j++] = ' ';
        else if (isalnum(dec[i]))
            msg[j++] = dec[i];
        else
            err_out(ERROR_INPUT);
    }
    *msglen = j;
    free(dec);
}
