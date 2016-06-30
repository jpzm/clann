/**
 * Copyright (C) 2008-2014 Joao Paulo de Souza Medeiros
 *
 * Author(s): Joao Paulo de Souza Medeiros <ignotus21@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef READER_H
#define READER_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clann.h"
#include "matrix.h"


/**
 * The following functions are used to read files that have only numerical
 * data (being it float-point or not), used mainly in to perform signal
 * processing algorithms.
 */

/**
 * Extract a vector from a line of numbers.
 *
 * @param m     A structure of matrix type
 * @param line  The line to be parsed
 */
void
reader_extract_numbers(struct matrix *m,
                       const char *line);

/**
 * Reader for input data files (with pairs of data, i.e. a input line followed
 * by a output line).
 *
 * @param path  X
 * @param x     X
 * @param d     X
 * @return      Return 0 (zero) for error and 1 (one) for success.
 */
int
reader_read_double_data_file(const char *path,
                             struct matrix *x,
                             struct matrix *d);

/**
 * Reader for multidimensional time series files.
 *
 * @param path  X
 * @return      Return 0 (zero) for error and 1 (one) for success.
 */
int
reader_read_data_file(const char *path,
                      struct matrix *v);

#endif
