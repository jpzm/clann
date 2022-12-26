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
#include "../code/som.h"
#include "../code/clann.h"
#include "../code/matrix.h"
#include "../code/io.h"


#define USAGE "Usage: som.o <training-file>\n"\
              "             <mesh-type>\n"\
              "             <width>\n"\
              "             <start-epoch>\n"\
              "             <end-epoch>\n"


unsigned int epochs;
int axis_y, axis_x, axis_z;
char *file;
clann_matrix_type x, a;
struct som ann;

int
main(int argc, char *argv[])
{
    if (argc == 6)
    {
        clann_initialize();

        clann_io_read_data_file(argv[1], &x);
        clann_size_type width = atoi(argv[3]);
        ann.epoch = atoi(argv[4]);
        epochs = atoi(argv[5]);

        som_initialize(&ann, atoi(argv[2]), x.cols, width);
        ann.step = 1;

        som_train_incremental(&ann, &x, epochs);

        som_save(&ann, "../save/save.som");
    }
    else
    {
        printf(USAGE);

        return 1;
    }

    return 0;
}
