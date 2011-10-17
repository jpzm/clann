/**
 * Copyright (C) 2011 Joao Paulo de Souza Medeiros
 *
 * Author(s): João Paulo de Souza Medeiros <jpsm1985@gmail.com>
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

#include "kmeans.h"

void
kmeans_initialize(struct kmeans *ann,
                  clann_size_type n_centers,
                  clann_size_type center_size,
                  clann_real_type noticeable_change_rate)
{
    ann->n_centers = n_centers;
    ann->center_size = center_size;
    ann->noticeable_change_rate = noticeable_change_rate;
    ann->old_centers = NULL;

    matrix_initialize(&ann->centers, ann->n_centers, ann->center_size);
    matrix_fill_rand(&ann->centers, -1, 1);
}

void
kmeans_finalize(struct kmeans *ann)
{
    matrix_finalize(&ann->centers);
}

void
kmeans_train(struct kmeans *ann,
             const struct matrix *x,
             clann_real_type learning_rate)
{
    clann_size_type s, i, *mess = malloc(sizeof(clann_size_type) * x->rows);
    clann_real_type e, distance, minimun, *sample, *winner = NULL;

    ann->old_centers = matrix_copy_new(&ann->centers);

    /*
     * Index vector used to shuffle the input presentation sequence
     */
    for (s = 0; s < x->rows; s++)
        mess[s] = s;

    do
    {
        /*
         * For each input in the shuffle list
         */
        clann_shuffle((clann_int_type *) mess, x->rows);

        e = 0;

        for (s = 0; s < x->rows; s++)
        {
            sample = matrix_value(x, mess[s], 0);

            /*
             * Find the center most closer to current input sample
             */
            minimun = metric_euclidean(sample,
                                       matrix_value(&ann->centers, 0, 0),
                                       ann->center_size);
            winner = matrix_value(&ann->centers, 0, 0);

            for (i = 1; i < ann->n_centers; i++)
            {
                distance = metric_euclidean(sample,
                                            matrix_value(&ann->centers, i, 0),
                                            ann->center_size);
                if (distance < minimun)
                {
                    minimun = distance;
                    winner = matrix_value(&ann->centers, i, 0);
                }
            }

            /*
             * Adjust winning center positions
             */
            for (i = 0; i < ann->center_size; i++)
                winner[i] += learning_rate * (sample[i] - winner[i]);
        }

        /*
         * Compute the mean of changes
         */
        for (i = 0; i < ann->n_centers; i++)
        {
            e += metric_euclidean(matrix_value(&ann->centers, i, 0),
                                  matrix_value(ann->old_centers, i, 0),
                                  ann->center_size);
        }

        e = e / ann->n_centers;
#if CLANN_VERBOSE
        printf("N. [KMEANS] Mean centers' update: " CLANN_PRINTF ".\n", e);
#endif
        matrix_copy(&ann->centers, ann->old_centers);
    }
    while (e > ann->noticeable_change_rate);

    free((void *) ann->old_centers);
    ann->old_centers = NULL;
}
