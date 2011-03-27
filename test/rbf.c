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

#include "../code/clann.h"
#include "../code/rbf.h"
#include "../code/matrix.h"
#include "../code/reader.h"

int main(int argc, char **argv)
{
    struct rbf r;
    struct matrix x, d, input_val;
    unsigned int i;

    clann_initialize();

    reader_read_double_data_file(argv[1], &x, &d);

    matrix_initialize(&input_val, 1, 2);

    *matrix_value(&input_val, 0, 0) = 1;
    *matrix_value(&input_val, 0, 1) = 1;

    rbf_initialize(&r, 2, 1, 4, 2);
    rbf_learn(&r, &x, &d);
    rbf_compute_output(&r, &input_val.values[0]);

    for (i = 0; i < r.output_size; i++)
        printf("output[%d]= " CLANN_PRINTF " \n", i, r.output[i]);

    return 0;
}
