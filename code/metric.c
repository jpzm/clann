/**
 * Copyright (C) 2008 Joao Paulo de Souza Medeiros
 * Copyright (C) 2009 Adriano Monteiro Marques
 *
 * Author(s): João Paulo de Souza Medeiros <ignotus21@gmail.com>
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

#include "metric.h"


clann_real_type
metric_scale(clann_real_type value,
             clann_real_type *from,
             clann_real_type *to)
{
    return (value - from[0]) * (to[1] - to[0]) / (from[1] - from[0]) + to[0];
}

clann_real_type
metric_euclidean_pow2(const clann_real_type *a,
                      const clann_real_type *b,
                      const unsigned int length)
{
    clann_real_type e, sum = 0;

    unsigned int i;
    for (i = 0; i < length; i++)
    {
        e = a[i] - b[i];
        sum += e * e;
    }

    return sum;
}

clann_real_type
metric_euclidean(const clann_real_type *a,
                 const clann_real_type *b,
                 const unsigned int length)
{
    clann_real_type e, sum = 0;

    unsigned int i;
    for (i = 0; i < length; i++)
    {
        e = a[i] - b[i];
        sum += e * e;
    }

    return CLANN_SQRT(sum);
}

clann_real_type
metric_norm(const clann_real_type *a,
            const unsigned int length)
{
    clann_real_type sum = 0;

    unsigned int i;
    for (i = 0; i < length; i++)
        sum += CLANN_POW(a[i], 2);

    return CLANN_SQRT(sum);
}

clann_real_type
metric_dot_product(const clann_real_type *a,
                   const clann_real_type *b,
                   const unsigned int length)
{
    clann_real_type sum = 0;

    unsigned int i;
    for (i = 0; i < length; i++)
        sum += a[i] * b[i];

    return sum;
}

clann_real_type
metric_hausdorff(const struct matrix *a,
                 const struct matrix *b)
{
    unsigned int i, j;
    clann_real_type inf,
               sup = 0,
               d,
               *x,
               *y;

    for (i = 0; i < a->rows; i++)
    {
        inf = (clann_real_type) INT_MAX;
        x = matrix_value(a, i, 0);

        for (j = 0; j < b->rows; j++)
        {
            y = matrix_value(b, j, 0);
            d = metric_euclidean(x, y, a->cols);

            if (d < inf)
                inf = d;
        }

        if (inf > sup)
            sup = inf;
    }

    return sup;
}

clann_real_type
metric_hausdorff_symmetric(const struct matrix *a,
                           const struct matrix *b)
{
    clann_real_type ab, ba; 

    ab = metric_hausdorff(a, b);
    ba = metric_hausdorff(b, a);

    return ab > ba ? ab : ba;
}

unsigned int
metric_hausdorff_limit(const struct matrix *a,
                       const struct matrix *b,
                       clann_real_type limit)
{
    unsigned int i, j, count = 0;
    clann_real_type inf,
               d,
               *x,
               *y;

    for (i = 0; i < a->rows; i++)
    {
        inf = (clann_real_type) INT_MAX;
        x = matrix_value(a, i, 0);

        for (j = 0; j < b->rows; j++)
        {
            y = matrix_value(b, j, 0);
            d = metric_euclidean(x, y, a->cols);

            if (d < inf)
                inf = d;
        }

        if (inf > limit)
            count++;
    }

    return count;
}

unsigned int
metric_hausdorff_limit_symmetric(const struct matrix *a,
                                 const struct matrix *b,
                                 clann_real_type limit)
{
    unsigned int ab, ba; 

    ab = metric_hausdorff_limit(a, b, limit);
    ba = metric_hausdorff_limit(b, a, limit);

    return ab > ba ? ab : ba;
}

clann_real_type
metric_hausdorff_mean(const struct matrix *a,
                      const struct matrix *b)
{
    unsigned int i, j;
    clann_real_type inf,
               mean = 0,
               d,
               *x,
               *y;

    for (i = 0; i < a->rows; i++)
    {
        inf = (clann_real_type) INT_MAX;
        x = matrix_value(a, i, 0);

        for (j = 0; j < b->rows; j++)
        {
            y = matrix_value(b, j, 0);
            d = metric_euclidean(x, y, a->cols);

            if (d < inf)
                inf = d;
        }

        mean += inf / (clann_real_type) a->rows;
    }

    return mean;
}

clann_real_type
metric_hausdorff_mean_symmetric(const struct matrix *a,
                                const struct matrix *b)
{
    clann_real_type ab, ba; 

    ab = metric_hausdorff_mean(a, b);
    ba = metric_hausdorff_mean(b, a);

    return ab > ba ? ab : ba;
}

unsigned int
metric_hausdorff_angle(const struct matrix *a,
                       const struct matrix *b,
                       clann_real_type limit)
{
    unsigned int i, j, length;
    clann_real_type inf,
               angle,
               count = 0,
               d,
               *x, *y,
               a_c[2], b_c[2];

    length = a->cols > b->cols ? b->cols - 1 : a->cols - 1;

    for (i = 0; i < a->rows; i++)
    {
        inf = (clann_real_type) INT_MAX;
        x = matrix_value(a, i, 0);

        for (j = 0; j < b->rows; j++)
        {
            y = matrix_value(b, j, 0);
            d = metric_euclidean(x, y, length);

            if (d < inf)
            {
                inf = d;
                angle = y[length];
            }
        }

        a_c[0] = CLANN_COS(x[length]);
        a_c[1] = CLANN_SIN(x[length]);

        b_c[0] = CLANN_COS(angle);
        b_c[1] = CLANN_SIN(angle);

        d = metric_dot_product(a_c, b_c, 2);

        if (d < 1 - limit)
            count++;
    }

    return count;
}

unsigned int
metric_hausdorff_angle_symmetric(const struct matrix *a,
                                 const struct matrix *b,
                                 clann_real_type limit)
{
    unsigned int ab, ba; 

    ab = metric_hausdorff_angle(a, b, limit);
    ba = metric_hausdorff_angle(b, a, limit);

    return ab > ba ? ab : ba;
}
