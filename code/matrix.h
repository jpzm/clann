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

#ifndef CLANN_MATRIX_H
#define CLANN_MATRIX_H

#include <stdlib.h>
#include "clann.h"


/**
 * Matrix structure
 */
typedef struct clann_matrix
{
    clann_real_type *values;
    clann_size_type rows;
    clann_size_type cols;
    clann_real_type max;
    clann_real_type min;
} clann_matrix_type;


/**
 * Initialize an given matrix
 */
clann_void_type
clann_matrix_initialize(clann_matrix_type *a,
                        clann_size_type rows,
                        clann_size_type cols);

/**
 * Create a new matrix
 */
clann_matrix_type *
clann_matrix_new(clann_size_type rows,
                 clann_size_type cols);

/**
 * Finalize an given matrix
 */
clann_void_type
clann_matrix_finalize(clann_matrix_type *a);

/**
 * Return an matrix element
 */
clann_real_type*
clann_matrix_value(const clann_matrix_type *a,
                   const clann_size_type i,
                   const clann_size_type j);

/**
 *
 */
clann_void_type
clann_matrix_fill(clann_matrix_type *a,
                  const clann_real_type v);

/**
 *
 */
clann_void_type
clann_matrix_fill_rand(clann_matrix_type *a,
                       clann_real_type min,
                       clann_real_type max);

/**
 *
 */
clann_matrix_type *
clann_matrix_identity(clann_matrix_type *a,
                      const clann_size_type n);

/**
 *
 */
clann_void_type
clann_matrix_copy(const clann_matrix_type *a,
                  clann_matrix_type *b);

/**
 *
 */
clann_matrix_type *
clann_matrix_copy_new(const clann_matrix_type *a);

/**
 *
 */
clann_void_type
clann_matrix_transpose(const clann_matrix_type *a,
                       clann_matrix_type *b);

/**
 *
 */
clann_matrix_type*
clann_matrix_add(const clann_matrix_type *a,
                 const clann_matrix_type *b,
                 clann_matrix_type *c);

/**
 *
 */
clann_matrix_type*
clann_matrix_subtract(const clann_matrix_type *a,
                      const clann_matrix_type *b,
                      clann_matrix_type *c);

/**
 *
 */
clann_matrix_type*
clann_matrix_product(const clann_matrix_type *a,
                     const clann_matrix_type *b,
                     clann_matrix_type *c);

/**
 *
 */
clann_matrix_type*
clann_matrix_inverse(const clann_matrix_type *a,
                     clann_matrix_type *b);

/**
 *
 */
clann_matrix_type*
clann_matrix_pseudo_inverse(const clann_matrix_type *a,
                            clann_matrix_type *b);

/**
 *
 */
clann_bool_type
clann_matrix_isnull(const clann_matrix_type *a);

/**
 *
 */
clann_void_type
clann_matrix_scale(const clann_matrix_type *a,
                   clann_real_type s);

/**
 *
 */
clann_void_type
clann_matrix_print(const clann_matrix_type *a);

#endif
