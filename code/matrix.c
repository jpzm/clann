/**
 * Copyright (C) 2008 Joao Paulo de Souza Medeiros
 * Copyright (C) 2009 Adriano Monteiro Marques
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
matrix_initialize(struct matrix *a,
                  const unsigned int rows,
                  const unsigned int cols)
{
    unsigned int size = rows * cols;

    if (size)
        a->values = (clann_real_type *) malloc(sizeof(clann_real_type) * size);
    else
        a->values = (clann_real_type *) NULL;

    a->rows = rows;
    a->cols = cols;
}

void
matrix_finalize(struct matrix *a)
{
    free((void *) a->values);
}

clann_real_type*
matrix_value(const struct matrix *a,
             const unsigned int i,
             const unsigned int j)
{
    if (i < a->rows && j < a->cols)
        return &a->values[a->cols * i + j];

    return (clann_real_type *) NULL;
}

void
matrix_fill(struct matrix *a,
            const clann_real_type v)
{
    unsigned int i;
    for (i = 0; i < a->rows * a->cols; i++)
        a->values[i] = v;
}

void
matrix_fill_rand(struct matrix *a,
                 clann_real_type min,
                 clann_real_type max)
{
    unsigned int i;
    for (i = 0; i < a->rows * a->cols; i++)
        a->values[i] = clann_rand(min, max);
}

void
matrix_identity(struct matrix *a,
                const unsigned int n)
{
    matrix_initialize(a, n, n);

    unsigned int i, j;
    for (i = 0; i < a->rows; i++)
        for (j = 0; j < a->cols; j++)
            *matrix_value(a, i, j) = (clann_real_type) (i == j) ? 1 : 0;
}

void
matrix_copy(const struct matrix *a,
            struct matrix *b)
{
    matrix_initialize(b, a->rows, a->cols);

    unsigned int i;
    for (i = 0; i < a->rows * a->cols; i++)
        b->values[i] = a->values[i];
}

void
matrix_transpose(const struct matrix *a,
                 struct matrix *b)
{
    matrix_initialize(b, a->cols, a->rows);

    unsigned int i, j;
    for (i = 0; i < b->rows; i++)
        for (j = 0; j < b->cols; j++)
            *matrix_value(b, i, j) = *matrix_value(a, j, i);
}

struct matrix*
matrix_add(const struct matrix *a,
           const struct matrix *b,
           struct matrix *c)
{
    if (a->rows != b->rows || a->cols != b->cols)
        return (struct matrix*) NULL;

    matrix_initialize(c, a->rows, a->cols);
    matrix_fill(c, 0);

    unsigned int i, j;
    for (i = 0; i < a->rows; i++)
        for (j = 0; j < a->cols; j++)
        {
            *matrix_value(c, i, j) += *matrix_value(a, i, j);
            *matrix_value(c, i, j) += *matrix_value(b, i, j);
        }

    return c;
}

struct matrix*
matrix_subtract(const struct matrix *a,
                const struct matrix *b,
                struct matrix *c)
{
    if (a->rows != b->rows || a->cols != b->cols)
        return (struct matrix*) NULL;

    matrix_initialize(c, a->rows, a->cols);
    matrix_fill(c, 0);

    unsigned int i, j;
    for (i = 0; i < a->rows; i++)
        for (j = 0; j < a->cols; j++)
        {
            *matrix_value(c, i, j) += *matrix_value(a, i, j);
            *matrix_value(c, i, j) -= *matrix_value(b, i, j);
        }

    return c;
}

struct matrix*
matrix_product(const struct matrix *a,
               const struct matrix *b,
               struct matrix *c)
{
    if (a->cols != b->rows)
        return (struct matrix*) NULL;

    matrix_initialize(c, a->rows, b->cols);
    matrix_fill(c, 0);

    unsigned int i, j, s;
    for (i = 0; i < c->rows; i++)
        for (j = 0; j < c->cols; j++)
            for (s = 0; s < a->cols; s++)
                *matrix_value(c, i, j) += (*matrix_value(a, i, s)) *
                                          (*matrix_value(b, s, j));

    return c;
}

struct matrix*
matrix_inverse(const struct matrix *a,
               struct matrix *b)
{
    if (a->rows != a->cols)
        return (struct matrix*) NULL;

    struct matrix c;

    matrix_copy(a, &c);
    matrix_identity(b, a->rows);

    unsigned int i, j, p = 0;
    clann_real_type v;

    while (p < a->rows)
    {
        v = *matrix_value(&c, p, p);

        if (v == 0)
            return (struct matrix*) NULL;

        for (i = 0; i < c.cols; i++)
        {
            *matrix_value(b, p, i) /= v;
            *matrix_value(&c, p, i) /= v;
        }

        for (i = 0; i < c.rows; i++)
        {
            if (i != p)
            {
                v = *matrix_value(&c, i, p);

                for (j = 0; j < c.cols; j++)
                {
                    *matrix_value(b, i, j) -= (*matrix_value(b, p, j)) * v;
                    *matrix_value(&c, i, j) -= (*matrix_value(&c, p, j)) * v;
                }
            }
        }

        p++;
    }

    return b;
}

struct matrix*
matrix_pseudo_inverse(const struct matrix *a,
                      struct matrix *b)
{
    struct matrix c, d, e;

    matrix_transpose(a, &c);

    if (matrix_product(&c, a, &d) == NULL)
        return (struct matrix*) NULL;

    if (matrix_inverse(&d, &e) == NULL)
        return (struct matrix*) NULL;

    matrix_product(&e, &c, b);

    matrix_finalize(&c);
    matrix_finalize(&d);
    matrix_finalize(&e);

    return b;
}

int
matrix_isnull(const struct matrix *a)
{
    unsigned int i;
    for (i = 0; i < a->rows * a->cols; i++)
        if (a->values[i] != (clann_real_type) 0)
            return 1;

    return 0;
}

void
matrix_print(const struct matrix *a)
{
    clann_size_type i, j;

    printf("["CLANN_SIZE_PRINTF", "CLANN_SIZE_PRINTF"]\n", a->rows, a->cols);
    
    for (i = 0; i < a->rows; i++)
    {
        for (j = 0; j < a->cols; j++)
            printf(CLANN_PRINTF" ", *matrix_value(a, i, j));
        printf("\n");
    }
}
