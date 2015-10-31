/*
 * error.c - simple error handling functions for b64pack
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

void err_out(const char *reason)
{
    fprintf(stderr, "Error: %s.\n", reason);
    exit(EXIT_FAILURE);
}

void err_sys(const char *function)
{
    perror(function);
    exit(EXIT_FAILURE);
}

void err_use(const char *progname)
{
    fprintf(stderr, "Usage: %s [-d]\n", progname);
    exit(EXIT_FAILURE);
}
