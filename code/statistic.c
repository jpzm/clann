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

#include "statistic.h"


clann_real_type
statistic_mean(const clann_real_type *list,
               const unsigned int length)
{
    unsigned int i;
    clann_real_type sum = 0;

    for (i = 0; i < length; i++)
        sum += list[i];

    return sum / length;
}

clann_real_type
statistic_mean_matrix(const clann_matrix_type *m)
{
    unsigned int i, j;
    clann_real_type sum = 0;

    for (i = 0; i < m->rows; i++)
        for (j = 0; j < m->cols; j++)
            sum += *clann_matrix_value(m, i, j);

    return sum / (m->rows * m->cols);
}

clann_real_type
statistic_mean_matrix_row(const clann_matrix_type *m,
                          const unsigned int row)
{
    unsigned int i;
    clann_real_type sum = 0;

    for (i = 0; i < m->cols; i++)
        sum += *clann_matrix_value(m, row, i);

    return sum / (m->cols);
}

clann_real_type
statistic_mean_matrix_col(const clann_matrix_type *m,
                          const unsigned int col)
{
    unsigned int i;
    clann_real_type sum = 0;

    for (i = 0; i < m->rows; i++)
        sum += *clann_matrix_value(m, i, col);

    return sum / (m->rows);
}

clann_real_type
statistic_variance(const clann_real_type *list,
                   const clann_real_type *probability,
                   const unsigned int length)
{
    unsigned int i;
    clann_real_type mean, sum = 0;

    mean = statistic_mean(list, length);

    for (i = 0; i < length; i++)
    {
        if (probability == NULL)
            sum += (1 / length) * CLANN_POW(list[i] - mean, 2.0);

        else
            sum += probability[i] * CLANN_POW(list[i] - mean, 2.0);
    }

    return sum;
}

clann_real_type
statistic_variance_matrix(const clann_matrix_type *m,
                          const clann_real_type *probability)
{
    unsigned int i, j;
    clann_real_type mean, sum = 0;

    mean = statistic_mean_matrix(m);

    for (i = 0; i < m->rows; i++)
        for (j = 0; j < m->cols; j++)
        {
            if (probability == NULL)
                sum += (1 / (m->rows * m->cols)) *
                       CLANN_POW(*clann_matrix_value(m, i, j) - mean, 2.0);

            else
                sum += probability[i] *
                       CLANN_POW(*clann_matrix_value(m, i, j) - mean, 2.0);
        }

    return sum;
}

clann_real_type
statistic_variance_matrix_row(const clann_matrix_type *m,
                              const clann_real_type *probability,
                              const unsigned int row)
{
    unsigned int i;
    clann_real_type mean, sum = 0;

    mean = statistic_mean_matrix_row(m, row);

    for (i = 0; i < m->cols; i++)
    {
        if (probability == NULL)
            sum += ((clann_real_type) 1 / m->cols) *
                   CLANN_POW(*clann_matrix_value(m, row, i) - mean, 2.0);

        else
            sum += probability[i] *
                   CLANN_POW(*clann_matrix_value(m, row, i) - mean, 2.0);
    }

    return sum;
}

clann_real_type
statistic_variance_matrix_col(const clann_matrix_type *m,
                              const clann_real_type *probability,
                              const unsigned int col)
{
    unsigned int i;
    clann_real_type mean, sum = 0;

    mean = statistic_mean_matrix_col(m, col);

    for (i = 0; i < m->rows; i++)
    {
        if (probability == NULL)
            sum += ((clann_real_type) 1 / m->rows) *
                   CLANN_POW(*clann_matrix_value(m, i, col) - mean, 2.0);

        else
            sum += probability[i] *
                   CLANN_POW(*clann_matrix_value(m, i, col) - mean, 2.0);
    }

    return sum;
}
