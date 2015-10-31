/*
 * b64pack.h - common header with constants and function prototypes
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

#ifndef _B64PACK_H_
#define _B64PACK_H_

/* input and output */

#define MSG_MINLEN       4
#define MSG_BLKSIZE   1024

size_t get_message(char **);
void   put_message(const char *, size_t);

/* compression and decompression */

#define OP_COMPRESS      0
#define OP_DECOMPRESS    1

void b64pack_compress(char *, size_t *);
void b64pack_decompress(char *, size_t *);

/* error handling */

#define ERROR_INPUT   "Invalid input. Accepting only printable characters"
#define ERROR_TRANS   "Invalid character in transcoded message"
#define ERROR_LENGTH  "Input too short. Expecting at least 4 characters"

void err_out(const char *);
void err_sys(const char *);
void err_use(const char *);

#endif
