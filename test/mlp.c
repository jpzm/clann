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

#include <stdlib.h>
#include <unistd.h>
#include "../code/mlp.h"
#include "../code/backprop.h"
#include "../code/clann.h"
#include "../code/matrix.h"
#include "../code/io.h"


#define USAGE "Usage: mlp <training-file>\n"\
              "           <learning-rate>\n"\
              "           <architecture>\n"


char *file;
clann_matrix_type x, y, a;
struct mlp ann;
unsigned int i, number_of_layers, *architecture;

int
main(int argc, char *argv[])
{
    if (argc > 3)
    {
        clann_initialize();

        clann_io_read_double_data_file(argv[1], &x, &y);

        clann_real_type learning_rate = atof(argv[2]);

        number_of_layers = (argc - 3);
        architecture = malloc(number_of_layers * sizeof(unsigned int));

        for (i = 3; i < argc; i++)
            architecture[i - 3] = atoi(argv[i]);

        mlp_initialize(&ann, architecture, number_of_layers);
        backprop_train(&ann, &x, &y, 0.0, learning_rate, 0.00001, 0);

        clann_real_type in[2] = {1.0, -1.0};
        mlp_forward_computation(&ann, in);

        printf(CLANN_PRINTF " \n", ann.output_layer->neurons[0].output);

        return 0;
    }
    else
    {
        printf(USAGE);

        return 1;
    }

    return 0;
}
