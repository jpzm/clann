/**
 * Copyright (C) 2008-2014 Joao Paulo de Souza Medeiros
 *
 * Author(s): Joao Paulo de Souza Medeiros <ignotus21@gmail.com>
 *            Jose Macedo Firmino Filho <macedofirmino@gmail.com>
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

#include "rbf.h"


clann_void_type
rbf_initialize(struct rbf *ann,
               clann_size_type input_size,
               clann_size_type output_size,
               clann_size_type n_inputs,
               clann_size_type n_centers)
{
    ann->input_size = input_size;
    ann->output_size = output_size;
    ann->n_inputs = n_inputs;
    ann->n_centers = n_centers;
    
    if (ann->n_centers > ann->n_inputs)
    {
        printf("E. [RBF] Number of centers exceeds number of inputs.\n");
        exit(EXIT_FAILURE);
    }

    ann->learning_strategy = RBF_LEARNING_SELF_ORGANIZED;
    ann->green_function = FUNCTION_GREEN_GAUSSIAN;

    ann->desired_error = 1e-7;
    ann->noticeable_change_rate = 1e-7;

    ann->learning_rate_centers = 1e-3;
    ann->learning_rate_weights = 1e-3;
    ann->learning_rate_spreads = 1e-3;

    ann->output = malloc(sizeof(clann_real_type) * output_size);
    ann->centers_width = malloc(sizeof(clann_real_type) * n_centers);

    clann_matrix_initialize(&ann->green, ann->n_inputs, ann->n_centers + 1);
    clann_matrix_initialize(&ann->centers, ann->n_centers, ann->input_size);
    clann_matrix_initialize(&ann->weights, ann->n_centers + 1, ann->output_size);
}

clann_void_type
rbf_finalize(struct rbf *ann)
{
    clann_matrix_finalize(&ann->green);
    clann_matrix_finalize(&ann->centers);
    clann_matrix_finalize(&ann->weights);

    free((clann_void_type *) ann->output);
    free((clann_void_type *) ann->centers_width);
}

clann_void_type
rbf_learn(struct rbf *ann,
          const clann_matrix_type *x,
          const clann_matrix_type *d)
{
    switch(ann->learning_strategy)
    {
        case RBF_LEARNING_FIXED:

            rbf_learning_with_fixed_centers(ann, x, d);
            break;

        case RBF_LEARNING_SUPERVISED:

            rbf_learning_supervised(ann, x, d);
            break;

        case RBF_LEARNING_SELF_ORGANIZED:

            rbf_learning_self_organized(ann, x, d);
            break;

        default:
            printf("E. [RBF] Invalid learning strategy.\n");
            exit(EXIT_FAILURE);
    }
}

clann_void_type
rbf_compute_green(struct rbf *ann,
                  const clann_matrix_type *x)
{
    clann_size_type i, j;
    clann_real_type v;

    for (i = 0; i < ann->green.rows; i++)
    {
        for (j = 0; j < ann->green.cols - 1; j++)
        {
            v = metric_euclidean_pow2(clann_matrix_value(x, i, 0),
                                      clann_matrix_value(&ann->centers, j, 0),
                                      ann->input_size);
            v = function_green_gaussian(ann->centers_width[j], v);
            *clann_matrix_value(&ann->green, i, j) = v;
        }

        *clann_matrix_value(&ann->green, i, j) = 1.0;
    }
}

clann_void_type
rbf_compute_weights(struct rbf *ann,
                    const clann_matrix_type *d)
{
    clann_matrix_type p;

    clann_matrix_initialize(&p, 0, 0);

    if (clann_matrix_pseudo_inverse(&ann->green, &p))
    {
        clann_matrix_finalize(&ann->weights);

        if (clann_matrix_product(&p, d, &ann->weights))
        {
            clann_matrix_finalize(&p);
            return;
        }
        else
            printf("E. [RBF] Problem computing weights.\n");
    }
    else
        printf("E. [RBF] Green matrix has no pseudo inverse.\n");

    exit(EXIT_FAILURE);
}

clann_void_type
rbf_compute_output(struct rbf *ann,
                   clann_real_type *x)
{
    clann_real_type v;
    clann_size_type i, j;

    for (i = 0; i < ann->output_size; i++)
    {
        ann->output[i] = 0;

        for (j = 0; j < ann->n_centers; j++)
        {
            v = metric_euclidean_pow2(x,
                                      clann_matrix_value(&ann->centers, j, 0),
                                      ann->input_size);
            v = function_green_gaussian(ann->centers_width[j], v);

            ann->output[i] += *clann_matrix_value(&ann->weights, j, i) * v;
        }

        ann->output[i] += *clann_matrix_value(&ann->weights, j, i);
    }
}

clann_void_type
rbf_learning_with_fixed_centers(struct rbf *ann,
                                const clann_matrix_type *x,
                                const clann_matrix_type *d)
{
    rbf_initialize_centers_at_random(ann, x);
    rbf_compute_center_widths(ann);
    rbf_compute_green(ann, x);
    rbf_compute_weights(ann, d);
}

clann_void_type
rbf_learning_supervised(struct rbf *ann,
                        const clann_matrix_type *x,
                        const clann_matrix_type *d)
{
    rbf_initialize_centers_at_random(ann, x);

    /* TODO: write the rest of the algorthm. */
}

clann_void_type
rbf_learning_self_organized(struct rbf *ann,
                            const clann_matrix_type *x,
                            const clann_matrix_type *d)
{
    clann_size_type i, j;
    clann_real_type e;
    struct kmeans k;
    struct neuron *n;
    struct lms l;

    /*
     * K-means clustering algorithm and in-place initialization
     */
    rbf_initialize_centers_at_random(ann, x);
    k.n_centers = ann->n_centers;
    k.center_size = ann->input_size;
    k.noticeable_change_rate = ann->noticeable_change_rate;
    k.centers = ann->centers;

    kmeans_train(&k, x, ann->learning_rate_centers);

#if CLANN_VERBOSE
    printf("N. [RBF] Centers: \n");
    clann_matrix_print(&ann->centers);
#endif
    /*
     * Compute Grenn's matrix to use as LMS inputs, initialize weights and
     * compute centers' widths
     */
    rbf_compute_center_widths(ann);
    rbf_compute_green(ann, x);
    clann_matrix_fill_rand(&ann->weights, -1, 1);

    /*
     * Computing weights using LMS algorthm
     */
    n = malloc(sizeof(struct neuron) * ann->output_size);

    lms_initialize(&l, ann->learning_rate_weights);


    for (i = 0; i < ann->output_size; i++)
    {
        /*
         * We do not initialize neurons because we just use its structure to
         * adjust weights using LMS
         */
        n[i].weights = clann_matrix_value(&ann->weights, i, 0);
        n[i].n_weights = ann->weights.rows - 1;
    }

    do
    {
        e = 0;

        for (i = 0; i < ann->n_inputs; i++)
        {
            for (j = 0; j < ann->output_size; j++)
            {
                lms_learn(&n[j],
                          &l,
                          clann_matrix_value(&ann->green, i, 0),
                          *clann_matrix_value(d, i, j));

                e += n[j].error * n[j].error;
            }
        }

        e = e / (ann->n_inputs * ann->output_size);
#if CLANN_VERBOSE
    printf("N. [RBF] LMS mean error: " CLANN_PRINTF ".\n", e);
#endif
    }
    while (e > ann->desired_error);

    free((clann_void_type *) n);
}


clann_void_type
rbf_compute_center_widths(struct rbf *ann)
{
    clann_size_type i, j, s;
    clann_real_type v, d, maximum = 0;

    for (i = 0; i < ann->centers.rows; i++)
    {
        for (j = 0; j < ann->centers.rows; j++)
        {
            v = 0;

            for (s = 0; s < ann->centers.cols; s++)
            {
                d = *clann_matrix_value(&ann->centers, i, s);
                d = d - *clann_matrix_value(&ann->centers, j, s);
                v += d * d;
            }

            v = CLANN_SQRT(v);

            if (v > maximum)
                maximum = v;
        }
    }

    v = maximum / CLANN_SQRT(2 * ann->n_centers);

    for (i = 0; i < ann->n_centers; i++)
        ann->centers_width[i] = v;
}

clann_void_type
rbf_initialize_centers_at_random(struct rbf *ann,
                                 const clann_matrix_type *x)
{
    clann_size_type *s, i, j, c = 0;
    clann_bool_type equal_flag = false;

    /*
     * Select centers from input a random
     */
    s = malloc(sizeof(clann_size_type) * ann->n_centers);

    while (c < ann->n_centers)
    {
        i = clann_randint(0, ann->n_inputs - 1);

        for (j = 0; j < c; j++)
            if (s[j] == i)
            {
                equal_flag = true;
                break;
            }

        if (equal_flag)
            equal_flag = false;
        else
            s[c++] = i;
    }

    for (i = 0; i < ann->centers.rows; i++)
    {
        for (j = 0; j < ann->centers.cols; j++)
            *clann_matrix_value(&ann->centers, i, j) = *clann_matrix_value(x, s[i], j);
    }
}
