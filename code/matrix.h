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

#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include "clann.h"


/**
 * Matrix structure
 */
struct matrix
{
    clann_real_type *values;
    clann_size_type rows;
    clann_size_type cols;
    clann_real_type max;
    clann_real_type min;
};


/**
 * Initialize an given matrix
 */
void
matrix_initialize(struct matrix *a,
                  clann_size_type rows,
                  clann_size_type cols);

/**
 * Create a new matrix
 */
struct matrix *
matrix_new(clann_size_type rows,
           clann_size_type cols);

/**
 * Finalize an given matrix
 */
void
matrix_finalize(struct matrix *a);

/**
 * Return an matrix element
 */
clann_real_type*
matrix_value(const struct matrix *a,
             const clann_size_type i,
             const clann_size_type j);

/**
 *
 */
void
matrix_fill(struct matrix *a,
            const clann_real_type v);

/**
 *
 */
void
matrix_fill_rand(struct matrix *a,
                 clann_real_type min,
                 clann_real_type max);

/**
 *
 */
struct matrix *
matrix_identity(struct matrix *a,
                const clann_size_type n);

/**
 *
 */
void
matrix_copy(const struct matrix *a,
            struct matrix *b);

/**
 *
 */
struct matrix *
matrix_copy_new(const struct matrix *a);

/**
 *
 */
void
matrix_transpose(const struct matrix *a,
                 struct matrix *b);

/**
 *
 */
struct matrix*
matrix_add(const struct matrix *a,
           const struct matrix *b,
           struct matrix *c);

/**
 *
 */
struct matrix*
matrix_subtract(const struct matrix *a,
                const struct matrix *b,
                struct matrix *c);

/**
 *
 */
struct matrix*
matrix_product(const struct matrix *a,
               const struct matrix *b,
               struct matrix *c);

/**
 *
 */
struct matrix*
matrix_inverse(const struct matrix *a,
               struct matrix *b);

/**
 *
 */
struct matrix*
matrix_pseudo_inverse(const struct matrix *a,
                      struct matrix *b);

/**
 *
 */
int
matrix_isnull(const struct matrix *a);

/**
 *
 */
void
matrix_scale(const struct matrix *a,
             clann_real_type s);

/**
 *
 */
void
matrix_print(const struct matrix *a);

#endif
