/**
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

#include <stdio.h>
#include <stdlib.h>
#include "../code/clann.h"
#include "../code/reader.h"
#include "../code/statistic.h"
#include "../code/fft.h"

int main(int argc, char** argv)
{
    struct matrix x;
    unsigned int i;
    clann_real_type mean;

    clann_initialize();

    reader_read_data_file(argv[1], &x);

    mean = statistic_mean_matrix_col(&x, 0);

    unsigned int n = x.rows;
    complex *cx = malloc(sizeof(complex) * n);

    for (i = 0; i < x.rows; i++)
    {
        cx[i] = *matrix_value(&x, i, 0) - mean;

        if (x.cols > 1)
            cx[i] += *matrix_value(&x, i, 1) * I;
    }

    fft(&cx, &n, FFT_FORWARD);

    for (i = 0; i < n; i++)
        printf("%f %fi\n",
                creal(cx[i]),
                cimag(cx[i]));

    return 0;
}
