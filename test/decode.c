/**
 * Copyright (C) 2008 Joao Paulo de Souza Medeiros.
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

#include "../code/perceptron.h"
#include "../code/reader.h"
#include <stdlib.h>


#define USAGE "Usage: questao6 <train_file> <validate_file> <eta> <epochs>\n"


int main(int argc, char *argv[])
{
    struct vector_set x_set, d_set, v_set, y_set;
    struct neuron n[3];

    if (argc == 5)
    {
        read_data_file(argv[1], &x_set, &d_set);
        read_data_file(argv[2], &v_set, &y_set);

        initialize_neuron(&n[0], &x_set.vector_size);
        initialize_neuron(&n[1], &x_set.vector_size);
        initialize_neuron(&n[2], &x_set.vector_size);
        n[0].function = FUNCTION_SIGNAL;
        n[1].function = FUNCTION_SIGNAL;
        n[2].function = FUNCTION_SIGNAL;

        unsigned int e, i, j;
        for (e = 0; e < atoi(argv[4]); e++)
            for (i = 0; i < x_set.number_of_vectors; i++)
                for (j = 0; j < d_set.vector_size; j++)
                    learn(&n[j],
                          &x_set.vectors[i * x_set.vector_size],
                          &d_set.vectors[i * d_set.vector_size + j],
                          atof(argv[3]));

        for (i = 0; i < v_set.number_of_vectors; i++)
        {
            for (j = 0; j < v_set.vector_size; j++)
                printf("%lf\t", v_set.vectors[i * v_set.vector_size + j]);

            printf("\n");

            for (j = 0; j < y_set.vector_size; j++)
            {
                compute_output(&n[j], &v_set.vectors[i * v_set.vector_size]);
                printf("%lf\t", n[j].output);
            }

            printf("\n");

            for (j = 0; j < y_set.vector_size; j++)
                printf("%lf\t", y_set.vectors[i * y_set.vector_size + j]);

            printf("(desired)\n\n");
        }

        free((void*) x_set.vectors);
        free((void*) d_set.vectors);
        free((void*) v_set.vectors);
        free((void*) y_set.vectors);
    }
    else
    {
        printf(USAGE);
        return 1;
    }

    return 0;
}
