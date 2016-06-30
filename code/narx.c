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

#include "narx.h"


clann_void_type
narx_initialize(struct narx *ann,
                unsigned int *architecture,
                const unsigned int number_of_layers,
                const unsigned int recurrency_size)
{
    ann->recurrency = recurrency_size;

    if (ann->recurrency >= architecture[0])
    {
        printf("E. [NARX] Input size less than the needed.\n");
        exit(EXIT_FAILURE);
    }

    ann->delay = architecture[0] - ann->recurrency;
    ann->input_size = ann->delay + ann->recurrency;
    ann->input = malloc(sizeof(clann_real_type) * (ann->delay + ann->recurrency));

    unsigned int i;
    for (i = 0; i < ann->delay + ann->recurrency; i++)
        ann->input[i] = 0;

    mlp_initialize(&ann->ann, architecture, number_of_layers);
}

clann_void_type
narx_finalize(struct narx *ann)
{
    free((clann_void_type *) ann->input);

    mlp_finalize(&ann->ann);
}

clann_void_type
narx_insert_input(struct narx *ann,
                  const clann_real_type x)
{
    unsigned int i;
    for (i = ann->delay - 1; i > 0; i--)
        ann->input[i] = ann->input[i - 1];

    ann->input[0] = x;

    for (i = ann->delay; i < ann->input_size - 1; i++)
        ann->input[i] = ann->input[i + 1];

    i = ann->input_size - 1;
    ann->input[i] = ann->ann.output_layer->neurons[0].output;
}

int
narx_save(struct narx *ann,
          const char *file)
{
    FILE *fd;

    if ((fd = fopen(file, "w")))
    {
        unsigned int i, j, k;
        struct mlp_layer *l;

        fprintf(fd, "%s\n", NARX_FILE_HEADER);

        fprintf(fd, "%d", ann->ann.architecture[0]);

        for (i = 1; i < ann->ann.number_of_layers; i++)
            fprintf(fd, " %d", ann->ann.architecture[i]);

        fprintf(fd, "\n" CLANN_PRINTF " %d", ann->ann.avarage_error,
                                             ann->recurrency);

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

    printf("E. [NARX] Can not open/create file to write.\n");

    return 0;
}

int
narx_open(struct narx *ann,
          const char *file)
{
    FILE *fd;

    if ((fd = fopen(file, "r")))
    {
        char *line = NULL;
        size_t len;

        getline(&line, &len, fd);

        if (!strncmp(NARX_FILE_HEADER, line, (4 > len ? len: 4)))
        {
            clann_matrix_type a, o, w, f;
            unsigned int i;
            int c = 1;

            clann_matrix_initialize(&a, 0, 0);
            clann_matrix_initialize(&o, 0, 0);
            clann_matrix_initialize(&w, 0, 0);
            clann_matrix_initialize(&f, 0, 0);

            getline(&line, &len, fd);
            clann_io_extract_numbers(&a, line);

            unsigned int arch[a.cols];
            for (i = 0; i < a.cols; i++)
                arch[i] = (unsigned int) a.values[i];

            getline(&line, &len, fd);
            clann_io_extract_numbers(&o, line);

            narx_initialize(ann, arch, a.cols, (unsigned int) o.values[1]);
            ann->ann.avarage_error = o.values[0];

            while (1)
            {
                if (getline(&line, &len, fd) == -1) break;

                if (c == 1)
                    clann_io_extract_numbers(&w, line);
                else
                    clann_io_extract_numbers(&f, line);

                c *= -1;
            }

            if (c == 1)
            {
                mlp_fill(&ann->ann, &w, &f);

                return 1;
            }

            printf("E. [NARX] Inconsistency in opened file.\n");
        }

        printf("E. [NARX] Opened file is not a NARX file.\n");
    }
    else
        printf("E. [NARX] Can not open file to read.\n");

    return 0;
}
