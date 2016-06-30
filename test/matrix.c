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

#include <stdio.h>
#include <stdlib.h>
#include "../code/clann.h"
#include "../code/matrix.h"

#define M 4
#define N 3

int main(int argc, char** argv)
{
    clann_matrix_type a, b;

    clann_initialize();

    clann_matrix_initialize(&a, M, N);
    clann_matrix_initialize(&b, 0, 0);

    clann_matrix_fill_rand(&a, -9, 9);

    /*
    *clann_matrix_value(&a, 0, 0) = 1;
    *clann_matrix_value(&a, 0, 1) = 2;
    *clann_matrix_value(&a, 0, 2) = 6;

    *clann_matrix_value(&a, 1, 0) = 3;
    *clann_matrix_value(&a, 1, 1) = 5;
    *clann_matrix_value(&a, 1, 2) = 4;

    *clann_matrix_value(&a, 2, 0) = 2;
    *clann_matrix_value(&a, 2, 1) = 6;
    *clann_matrix_value(&a, 2, 2) = 8;

    *clann_matrix_value(&a, 3, 0) = 1;
    *clann_matrix_value(&a, 3, 1) = 0;
    *clann_matrix_value(&a, 3, 2) = 2;
    */

    printf("Matrix:\n");
    clann_matrix_print(&a);

    if (clann_matrix_pseudo_inverse(&a, &b) != NULL)
    {
        printf("Pseudo-inverse:\n");
        clann_matrix_print(&b);
    }
    else
        printf("No pseudo-inverse.\n");

    return 0;
}
