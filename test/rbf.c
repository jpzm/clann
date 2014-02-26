/**
 * Copyright (C) 2009-2014 Joao Paulo de Souza Medeiros
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
    struct matrix x, d;
    clann_size_type i;

    clann_initialize();

    reader_read_double_data_file(argv[1], &x, &d);

    rbf_initialize(&r, 2, 1, 4, 4);
    //r.learning_strategy = RBF_LEARNING_FIXED;
    rbf_learn(&r, &x, &d);

    printf("centers:\n");
    matrix_print(&r.centers);

    printf("input:\n");
    matrix_print(&x);

    printf("output:\n");
    for (i = 0; i < x.rows; i++)
    {
        rbf_compute_output(&r, matrix_value(&x, i, 0));
        printf(CLANN_PRINTF "\n", r.output[0]);
    }

    return 0;
}
