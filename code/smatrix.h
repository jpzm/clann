/**
 * Copyright (C) 2010-2011 Joao Paulo de Souza Medeiros
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

#ifndef SMATRIX_H
#define SMATRIX_H

#include <stdlib.h>
#include "clann.h"

#define SMATRIX_DEFAULT_VALUE   0


/**
 *
 */
struct value
{
    unsigned long int row;
    unsigned long int col;
    clann_real_type value;
};

/**
 * Sparse matrix structure
 */
struct smatrix
{
//    clann_list_type *l_values;
    unsigned long int rows;
    unsigned long int cols;
};


/**
 * Initialize a given matrix
 */
inline void
matrix_initialize(struct smatrix *a,
                  const unsigned long int rows,
                  const unsigned long int cols);

/**
 * Finalize a given matrix
 */
inline void
matrix_finalize(struct smatrix *a);

/**
 * Return a matrix element
 */
inline clann_real_type*
matrix_value(const struct smatrix *a,
             const unsigned int i,
             const unsigned int j);

/**
 *
 */
inline void
matrix_fill(struct smatrix *a,
            const clann_real_type v);

/**
 *
 */
inline void
matrix_identity(struct smatrix *a,
                const unsigned int n);

/**
 *
 */
inline void
matrix_copy(const struct smatrix *a,
            struct smatrix *b);

/**
 *
 */
inline void
matrix_transpose(const struct smatrix *a,
                 struct smatrix *b);

/**
 *
 */
inline struct smatrix*
matrix_add(const struct smatrix *a,
           const struct smatrix *b,
           struct smatrix *c);

/**
 *
 */
inline struct smatrix*
matrix_subtract(const struct smatrix *a,
                const struct smatrix *b,
                struct smatrix *c);

/**
 *
 */
inline struct smatrix*
matrix_product(const struct smatrix *a,
               const struct smatrix *b,
               struct smatrix *c);

/**
 *
 */
inline struct smatrix*
matrix_inverse(const struct smatrix *a,
               struct smatrix *b);

/**
 *
 */
inline struct smatrix*
matrix_pseudo_inverse(const struct smatrix *a,
                      struct smatrix *b);

/**
 *
 */
inline int
matrix_isnull(const struct smatrix *a);

#endif
