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

#include "matrix.h"


void
clann_matrix_initialize(clann_matrix_type *a,
                        clann_size_type rows,
                        clann_size_type cols)
{
    clann_size_type size = rows * cols;

    if (size)
    {
        a->values = (clann_real_type *) malloc(sizeof(clann_real_type) * size);
        a->rows = rows;
        a->cols = cols;
    }
    else
    {
        a->values = (clann_real_type *) NULL;
        a->rows = 0;
        a->cols = 0;
    }
}

clann_matrix_type *
clann_matrix_new(clann_size_type rows,
                 clann_size_type cols)
{
    clann_matrix_type *m = (clann_matrix_type *) malloc(sizeof(clann_matrix_type));
    clann_matrix_initialize(m, rows, cols);
    return m;
}

void
clann_matrix_finalize(clann_matrix_type *a)
{
    if (a->values != NULL)
        free((void *) a->values);

    a->values = (clann_real_type *) NULL;
    a->rows = 0;
    a->cols = 0;
}

clann_real_type*
clann_matrix_value(const clann_matrix_type *a,
                   const clann_size_type i,
                   const clann_size_type j)
{
    if (i < a->rows && j < a->cols)
        return &a->values[a->cols * i + j];

    return (clann_real_type *) NULL;
}

void
clann_matrix_fill(clann_matrix_type *a,
                  const clann_real_type v)
{
    clann_size_type i;
    for (i = 0; i < a->rows * a->cols; i++)
        a->values[i] = v;
}

void
clann_matrix_fill_rand(clann_matrix_type *a,
                       clann_real_type min,
                       clann_real_type max)
{
    clann_size_type i;
    for (i = 0; i < a->rows * a->cols; i++)
        a->values[i] = clann_rand(min, max);
}

clann_matrix_type *
clann_matrix_identity(clann_matrix_type *a,
                      const clann_size_type n)
{
    if (a->rows != n || a->cols != n)
    {
        clann_matrix_finalize(a);
        clann_matrix_initialize(a, n, n);
    }

    clann_size_type i, j;
    for (i = 0; i < a->rows; i++)
        for (j = 0; j < a->cols; j++)
            *clann_matrix_value(a, i, j) = (clann_real_type) (i == j) ? 1 : 0;

    return a;
}

void
clann_matrix_copy(const clann_matrix_type *a,
                  clann_matrix_type *b)
{
    if (b->rows != a->rows || b->cols != a->cols)
    {
        clann_matrix_finalize(b);
        clann_matrix_initialize(b, a->rows, a->cols);
    }

    clann_size_type i;
    for (i = 0; i < a->rows * a->cols; i++)
        b->values[i] = a->values[i];
}

clann_matrix_type *
clann_matrix_copy_new(const clann_matrix_type *a)
{
    clann_matrix_type *b = malloc(sizeof(clann_matrix_type));

    clann_matrix_initialize(b, a->rows, a->cols);
    clann_matrix_copy(a, b);

    return b;
}

void
clann_matrix_transpose(const clann_matrix_type *a,
                       clann_matrix_type *b)
{
    if (b->rows != a->cols || b->cols != a->rows)
    {
        clann_matrix_finalize(b);
        clann_matrix_initialize(b, a->cols, a->rows);
    }

    clann_size_type i, j;
    for (i = 0; i < b->rows; i++)
        for (j = 0; j < b->cols; j++)
            *clann_matrix_value(b, i, j) = *clann_matrix_value(a, j, i);
}

clann_matrix_type*
clann_matrix_add(const clann_matrix_type *a,
                 const clann_matrix_type *b,
                 clann_matrix_type *c)
{
    if (a->rows != b->rows || a->cols != b->cols)
        return (clann_matrix_type*) NULL;

    if (c->rows != a->rows || c->cols != b->cols)
    {
        clann_matrix_finalize(c);
        clann_matrix_initialize(c, a->rows, b->cols);
    }

    clann_size_type i, j;
    for (i = 0; i < a->rows; i++)
        for (j = 0; j < a->cols; j++)
            *clann_matrix_value(c, i, j) = *clann_matrix_value(a, i, j) +
                                           *clann_matrix_value(b, i, j);

    return c;
}

clann_matrix_type*
clann_matrix_subtract(const clann_matrix_type *a,
                      const clann_matrix_type *b,
                      clann_matrix_type *c)
{
    if (a->rows != b->rows || a->cols != b->cols)
        return (clann_matrix_type*) NULL;

    if (c->rows != a->rows || c->cols != b->cols)
    {
        clann_matrix_finalize(c);
        clann_matrix_initialize(c, a->rows, b->cols);
    }

    clann_size_type i, j;
    for (i = 0; i < a->rows; i++)
        for (j = 0; j < a->cols; j++)
            *clann_matrix_value(c, i, j) = *clann_matrix_value(a, i, j) -
                                           *clann_matrix_value(b, i, j);

    return c;
}

clann_matrix_type*
clann_matrix_product(const clann_matrix_type *a,
                     const clann_matrix_type *b,
                     clann_matrix_type *c)
{
    if (a->cols != b->rows)
        return (clann_matrix_type *) NULL;

    if (c->rows != a->rows || c->cols != b->cols)
    {
        clann_matrix_finalize(c);
        clann_matrix_initialize(c, a->rows, b->cols);
    }

    clann_matrix_fill(c, 0);

    clann_size_type i, j, s;
    for (i = 0; i < c->rows; i++)
        for (j = 0; j < c->cols; j++)
            for (s = 0; s < a->cols; s++)
                *clann_matrix_value(c, i, j) += (*clann_matrix_value(a, i, s)) *
                                                (*clann_matrix_value(b, s, j));

    return c;
}

clann_matrix_type*
clann_matrix_inverse(const clann_matrix_type *a,
                     clann_matrix_type *b)
{
    if (a->rows != a->cols)
        return (clann_matrix_type*) NULL;

    clann_matrix_type c;

    clann_matrix_initialize(&c, 0, 0);

    clann_matrix_copy(a, &c);
    clann_matrix_identity(b, a->rows);

    clann_size_type i, j, p = 0;
    clann_real_type v;

    while (p < a->rows)
    {
        v = *clann_matrix_value(&c, p, p);

        if (v == 0)
            return (clann_matrix_type*) NULL;

        for (i = 0; i < c.cols; i++)
        {
            *clann_matrix_value(b, p, i) /= v;
            *clann_matrix_value(&c, p, i) /= v;
        }

        for (i = 0; i < c.rows; i++)
        {
            if (i != p)
            {
                v = *clann_matrix_value(&c, i, p);

                for (j = 0; j < c.cols; j++)
                {
                    *clann_matrix_value(b, i, j) -= (*clann_matrix_value(b, p, j)) * v;
                    *clann_matrix_value(&c, i, j) -= (*clann_matrix_value(&c, p, j)) * v;
                }
            }
        }

        p++;
    }

    clann_matrix_finalize(&c);

    return b;
}

clann_matrix_type*
clann_matrix_pseudo_inverse(const clann_matrix_type *a,
                            clann_matrix_type *b)
{
    clann_matrix_type c, d, e;

    clann_matrix_initialize(&c, 0, 0);
    clann_matrix_initialize(&d, 0, 0);
    clann_matrix_initialize(&e, 0, 0);

    clann_matrix_transpose(a, &c);

    if (clann_matrix_product(&c, a, &d) == NULL)
        return (clann_matrix_type*) NULL;

    if (clann_matrix_inverse(&d, &e) == NULL)
        return (clann_matrix_type*) NULL;

    clann_matrix_product(&e, &c, b);

    clann_matrix_finalize(&c);
    clann_matrix_finalize(&d);
    clann_matrix_finalize(&e);

    return b;
}

clann_bool_type
clann_matrix_isnull(const clann_matrix_type *a)
{
    clann_size_type i;
    for (i = 0; i < a->rows * a->cols; i++)
        if (a->values[i] != (clann_real_type) 0)
            return true;

    return false;
}

void
clann_matrix_scale(const clann_matrix_type *a,
                   clann_real_type s)
{
    clann_size_type i;
    for (i = 0; i < a->rows * a->cols; i++)
        a->values[i] = a->values[i] * s;
}

void
clann_matrix_print(const clann_matrix_type *a)
{
    clann_size_type i, j;

    printf("["CLANN_SIZE_PRINTF", "CLANN_SIZE_PRINTF"]\n", a->rows, a->cols);
    
    for (i = 0; i < a->rows; i++)
    {
        for (j = 0; j < a->cols; j++)
            printf(CLANN_PRINTF" ", *clann_matrix_value(a, i, j));
        printf("\n");
    }
}
