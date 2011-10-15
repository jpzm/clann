/**
 * Copyright (C) 2008 Joao Paulo de Souza Medeiros
 * Copyright (C) 2009 Adriano Monteiro Marques
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

#include "som.h"


void
som_initialize(struct som *ann,
               som_grid_type grid_type,
               clann_size_type input_size,
               clann_size_type width)
{
    ann->input_size = input_size;
    ann->grid.width = width;
    ann->learning_rate = 0.1;
    ann->const_1 = 1000 / CLANN_LOG(ann->grid.width);
    ann->const_2 = 1000;
    ann->step = 1;
    ann->epoch = 1;
    ann->grid.type = grid_type;

    switch (ann->grid.type)
    {
        case SOM_GRID_LINE:
            ann->grid.dimension = SOM_GRID_1D;
            break;
        case SOM_GRID_SQUARE:
            ann->grid.dimension = SOM_GRID_2D;
            break;
        case SOM_GRID_CUBE:
            ann->grid.dimension = SOM_GRID_3D;
    }

    /*
     * Compute the number of neurons and initialize weights
     */
    ann->grid.n_neurons = CLANN_POW(ann->grid.width, ann->grid.dimension);

    matrix_initialize(&ann->grid.indexes,
                      ann->grid.n_neurons,
                      ann->grid.dimension);

    matrix_initialize(&ann->grid.weights,
                      ann->grid.n_neurons,
                      ann->input_size);

    matrix_fill_rand(&ann->grid.weights, -1, 1);

    /*
     * Generate the indexes
     */
    clann_size_type count = 0;
    clann_real_type *buffer;
    
    buffer = malloc(sizeof(clann_real_type) * ann->grid.dimension);

    som_grid_indexes(ann, 0, buffer, &count);

    free(buffer);
}

void
som_grid_indexes(struct som *ann,
                 clann_size_type index,
                 clann_real_type *buffer,
                 clann_size_type *count)
{
    unsigned int i;

    if (index < ann->grid.dimension)
    {
        for (i = 0; i < ann->grid.width; i++)
        {
            buffer[index] = i;
            som_grid_indexes(ann, index + 1, buffer, count);
        }
    }
    else
    {
        for (i = 0; i < ann->grid.dimension; i++)
            *matrix_value(&ann->grid.indexes, *count, i) = buffer[i];
        *count += 1;
    }
}

void
som_finalize(struct som *ann)
{
    matrix_finalize(&ann->grid.weights);
}

clann_real_type*
som_grid_get_weights(struct som *ann,
                     unsigned int index)
{
    return matrix_value(&ann->grid.weights, index, 0);
}

void
som_adjust_width(struct som *ann)
{
    clann_real_type aux;

    aux = - (clann_real_type) ann->epoch / ann->const_1;
    aux = ann->grid.width * CLANN_EXP(aux);
    ann->actual_width = 2 * aux * aux;
}

void
som_adjust_learning_rate(struct som *ann)
{
    clann_real_type aux;

    aux = CLANN_EXP(-((clann_real_type) ann->epoch / ann->const_2));
    ann->actual_learning_rate = ann->learning_rate * aux;
}

clann_real_type
som_compute_neighborhood_distance(struct som *ann,
                                  clann_real_type *p,
                                  clann_real_type *winner)
{
    clann_real_type d = metric_euclidean(p, winner, ann->grid.dimension);
    return CLANN_EXP(- (d * d) / ann->actual_width);
}

void
som_train_incremental(struct som *ann,
                      struct matrix *x,
                      unsigned int epochs)
{
    clann_real_type *sample, *winner = NULL;
    unsigned int s, mess[x->rows];

    /*
     * Index vector used to shuffle the input presentation sequence
     */
    for (s = 0; s < x->rows; s++)
        mess[s] = s;

    while (ann->epoch <= epochs)
    {
        clann_shuffle(mess, x->rows);

        som_adjust_width(ann);
        som_adjust_learning_rate(ann);

        /*
         * For each input sample `s'
         */
        for (s = 0; s < x->rows; s++)
        {
            sample = matrix_value(x, mess[s], 0);

            som_find_winner_neuron(ann, sample, &winner);
            som_incremental_adjust_of_weights(ann, sample, winner);
        }

#if CLANN_VERBOSE
        printf("N. [SOM] Width: "CLANN_PRINTF", Rate: "CLANN_PRINTF" (%d).\n",
               ann->actual_width,
               ann->actual_learning_rate,
               ann->epoch);
#endif
        ann->epoch += ann->step;
    }
}

void
som_train_batch(struct som *ann,
                struct matrix *x,
                unsigned int epochs)
{
    clann_real_type *sample, *winner = NULL;
    unsigned int s;

    while (ann->epoch <= epochs)
    {
        som_adjust_width(ann);

        /*
         * For each input sample `s'
         */
        for (s = 0; s < x->rows; s++)
        {
            sample = matrix_value(x, s, 0);

            som_find_winner_neuron(ann, sample, &winner);
            som_batch_adjust_of_weights(ann, sample, winner);
        }

#if CLANN_VERBOSE
        printf("N. [SOM] Width: "CLANN_PRINTF", Rate: "CLANN_PRINTF" (%d).\n",
               ann->actual_width,
               ann->actual_learning_rate,
               ann->epoch);
#endif
        ann->epoch += ann->step;
    }
}

void
som_incremental_adjust_of_weights(struct som *ann,
                                  clann_real_type *x,
                                  clann_real_type *winner)
{
    clann_real_type *w, *p, h;
    clann_size_type i, k;

    for (i = 0; i < ann->grid.n_neurons; i++)
    {
        p = matrix_value(&ann->grid.indexes, i, 0);
        w = matrix_value(&ann->grid.weights, i, 0);
        h = som_compute_neighborhood_distance(ann, p, winner);

        for (k = 0; k < ann->input_size; k++)
            w[k] += ann->actual_learning_rate * h * (x[k] - w[k]);
    }
}

void
som_batch_adjust_of_weights(struct som *ann,
                            clann_real_type *x,
                            clann_real_type *winner)
{
    // TODO
}

void
som_find_winner_neuron(struct som *ann,
                       clann_real_type *x,
                       clann_real_type **winner)
{
    clann_real_type *w, distance, minimun = (clann_real_type) INT_MAX;
    clann_size_type i;

    for (i = 0; i < ann->grid.n_neurons; i++)
    {
        w = matrix_value(&ann->grid.weights, i, 0);
        distance = metric_euclidean(x, w, ann->input_size);

        if (distance < minimun)
        {
            minimun = distance;
            *winner = matrix_value(&ann->grid.indexes, i, 0);
        }
    }
}

int
som_save(struct som *ann,
         const char *file)
{
    FILE *fd;

    if ((fd = fopen(file, "w")))
    {
        unsigned int i, j;

        fprintf(fd, "%s\n", FILE_HEADER_SOM);

        fprintf(fd, CLANN_SIZE_PRINTF" ", ann->input_size);
        fprintf(fd, CLANN_SIZE_PRINTF" ", ann->grid.width);
        fprintf(fd, CLANN_PRINTF" ", ann->learning_rate);
        fprintf(fd, CLANN_PRINTF" ", ann->const_1);
        fprintf(fd, CLANN_PRINTF"\n", ann->const_2);

        for (i = 0; i < ann->grid.weights.rows; i++)
        {
            fprintf(fd,
                    CLANN_PRINTF,
                    *matrix_value(&ann->grid.weights, i, 0));

            for (j = 1; j < ann->grid.weights.cols; j++)
                fprintf(fd,
                        " " CLANN_PRINTF,
                        *matrix_value(&ann->grid.weights, i, j));

            fprintf(fd, "\n");
        }

        fclose(fd);

        return 1;
    }

    printf("E. [SOM] Can not open/create file to write.\n");

    return 0;
}

int
som_open(struct som *ann,
         const char *file)
{
    // TODO
    return 0;
}
