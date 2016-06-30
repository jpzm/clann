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

#ifndef CLANN_IO_H
#define CLANN_IO_H

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
clann_void_type
clann_io_extract_numbers(clann_matrix_type *m,
                         const clann_string_type line);

/**
 * Reader for input data files (with pairs of data, i.e. a input line followed
 * by a output line).
 *
 * @param path  X
 * @param x     X
 * @param d     X
 * @return      Return false (zero) for error and true (one) for success.
 */
clann_bool_type
clann_io_read_double_data_file(const clann_string_type path,
                               clann_matrix_type *x,
                               clann_matrix_type *d);

/**
 * Reader for multidimensional time series files.
 *
 * @param path  X
 * @return      Return 0 (zero) for error and 1 (one) for success.
 */
clann_bool_type
clann_io_read_data_file(const clann_string_type path,
                        clann_matrix_type *v);

#endif
