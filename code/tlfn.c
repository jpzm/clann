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

#include "tlfn.h"


void
tlfn_initialize(struct tlfn *ann,
                unsigned int *architecture,
                const unsigned int number_of_layers)
{
    ann->input_size = architecture[0];
    ann->input = malloc(sizeof(clann_real_type) * ann->input_size);

    unsigned int i;
    for (i = 0; i < ann->input_size; i++)
        ann->input[i] = 0;

    mlp_initialize(&ann->ann, architecture, number_of_layers);
}

void
tlfn_finalize(struct tlfn *ann)
{
    free((void *) ann->input);

    mlp_finalize(&ann->ann);
}

void
tlfn_insert_input(struct tlfn *ann,
                  const clann_real_type x)
{
    unsigned int i;
    for (i = ann->input_size - 1; i > 0; i--)
        ann->input[i] = ann->input[i - 1];

    ann->input[0] = x;
}

int
tlfn_save(struct tlfn *ann,
          const char *file)
{
    FILE *fd;

    if ((fd = fopen(file, "w")))
    {
        unsigned int i, j, k;
        struct mlp_layer *l;

        fprintf(fd, "%s\n", TLFN_FILE_HEADER);

        fprintf(fd, "%d", ann->ann.architecture[0]);

        for (i = 1; i < ann->ann.number_of_layers; i++)
            fprintf(fd, " %d", ann->ann.architecture[i]);

        fprintf(fd, "\n" CLANN_PRINTF, ann->ann.avarage_error);

        for (i = 0; i < ann->ann.number_of_layers - 1; i++)
        {
            l = &ann->ann.layers[i];

            for (j = 0; j < l->size; j++)
            {
                fprintf(fd, "\n" CLANN_PRINTF, l->neurons[j].weights[0]);

                for (k = 1; k <= l->neurons[j].n_weights; k++)
                    fprintf(fd, " " CLANN_PRINTF, l->neurons[j].weights[k]);

                fprintf(fd, "\n%d", l->neurons[j].activation_function);
            }
        }

        fclose(fd);

        return 1;
    }

    printf("E. [TLFN] Can not open/create file for write.\n");

    return 0;
}


int
tlfn_open(struct tlfn *ann,
          const char *file)
{
    FILE *fd;

    if ((fd = fopen(file, "r")))
    {
        char *line = NULL;
        size_t len;

        getline(&line, &len, fd);

        if (!strncmp(TLFN_FILE_HEADER, line, (4 > len ? len: 4)))
        {
            struct matrix a, o, w, f;
            unsigned int i;
            int c = 1;

            matrix_initialize(&a, 0, 0);
            matrix_initialize(&o, 0, 0);
            matrix_initialize(&w, 0, 0);
            matrix_initialize(&f, 0, 0);

            getline(&line, &len, fd);
            reader_extract_numbers(&a, line);

            unsigned int arch[a.cols];
            for (i = 0; i < a.cols; i++)
                arch[i] = (unsigned int) a.values[i];

            getline(&line, &len, fd);
            reader_extract_numbers(&o, line);

            tlfn_initialize(ann, arch, a.cols);
            ann->ann.avarage_error = o.values[0];

            while (1)
            {
                if (getline(&line, &len, fd) == -1) break;

                if (c == 1)
                    reader_extract_numbers(&w, line);
                else
                    reader_extract_numbers(&f, line);

                c *= -1;
            }

            if (c == 1)
            {
                mlp_fill(&ann->ann, &w, &f);

                return 1;
            }

            printf("E. [TLFN] Inconsistency in opened file.\n");
        }

        printf("E. [TLFN] Opened file is not a TLFN file.\n");
    }
    else
        printf("E. [TLFN] Can not open file to read.\n");

    return 0;
}
