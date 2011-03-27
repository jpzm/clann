/**
 * Copyright (C) 2008 Joao Paulo de Souza Medeiros
 * Copyright (C) 2009 Adriano Monteiro Marques
 *
 * Author(s): João Paulo de Souza Medeiros <ignotus21@gmail.com>
 *            José Macedo Firmino Filho <macedofirmino@gmail.com>
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


void
rbf_initialize(struct rbf *r,
               const unsigned int input_size,
               const unsigned int output_size,
               const unsigned int number_of_inputs,
               const unsigned int number_of_centers)
{
    r->input_size = input_size;
    r->output_size = output_size;
    r->number_of_inputs = number_of_inputs;
    r->number_of_centers = number_of_centers;

    r->learning_strategy = RBF_LEARNING_SELF_ORGANIZED;
    r->green_function = FUNCTION_GREEN_GAUSSIAN;

    r->desired_error = 1e-5;
    r->noticeable_change_rate = 1e-5;

    r->learning_rate_centers = 1e-5;
    r->learning_rate_weights = 1e-3;
    r->learning_rate_spreads = 1e-3;

    r->output = malloc(sizeof(clann_real_type) * output_size);
    r->centers_width = malloc(sizeof(clann_real_type) * number_of_centers);

    matrix_initialize(&r->green, number_of_inputs, number_of_centers + 1);
    matrix_initialize(&r->centers, input_size, number_of_centers);
    matrix_initialize(&r->weights, number_of_centers + 1, output_size);
}

void
rbf_finalize(struct rbf *r)
{
    matrix_finalize(&r->green);
    matrix_finalize(&r->centers);
    matrix_finalize(&r->weights);

    free((void *) r->output);
    free((void *) r->centers_width);
}

void
rbf_learn(struct rbf *r,
          const struct matrix *x,
          const struct matrix *d)
{
    switch(r->learning_strategy)
    {
        case RBF_LEARNING_FIXED:

            rbf_learning_with_fixed_centers(r, x, d);
            break;

        case RBF_LEARNING_SUPERVISED:

            rbf_learning_supervised(r, x, d);
            break;

        case RBF_LEARNING_SELF_ORGANIZED:

            rbf_learning_self_organized(r, x, d);
            break;

        default:
            printf("E. [RBF] Invalid learning strategy.\n");
            exit(EXIT_FAILURE);
    }
}

void
rbf_compute_green(struct rbf *r,
                  const struct matrix *x)
{
    unsigned int i, j, s;
    clann_real_type v;

    for (i = 0; i < r->green.rows; i++)
    {
        for (j = 0; j < r->green.cols - 1; j++)
        {
            v = 0;

            for (s = 0; s < r->input_size; s++)
                v += CLANN_POW(*matrix_value(x, i, s) -
                               *matrix_value(&r->centers, s, j),
                               2);

            v = function_green_gaussian(&r->centers_width[j], &v);
            *matrix_value(&r->green, i, j) = v;
        }

        *matrix_value(&r->green, i, j) = 1.0;
    }
}

void
rbf_compute_weights(struct rbf *r,
                    const struct matrix *d)
{
    struct matrix p;

    if (matrix_pseudo_inverse(&r->green, &p))
    {
        matrix_finalize(&r->weights);

        if (matrix_product(&p, d, &r->weights))
        {
            matrix_finalize(&p);
            return;
        }
        else
            printf("E. [RBF] Problem computing weights.\n");
    }
    else
        printf("E. [RBF] Green matrix has no pseudo inverse.\n");

    exit(EXIT_FAILURE);
}

void
rbf_compute_output(struct rbf *r,
                   const clann_real_type *x)
{
    clann_real_type v;

    unsigned int i, j, s;
    for (i = 0; i < r->output_size; i++)
    {
        r->output[i] = 0;

        for (j = 0; j < r->number_of_centers; j++)
        {
            v = 0;

            for (s = 0; s < r->input_size; s++)
                v += CLANN_POW(x[s] - *matrix_value(&r->centers, s, j), 2);

            v = function_green_gaussian(&r->centers_width[j], &v);

            r->output[i] += *matrix_value(&r->weights, j, i) * v;
        }

        r->output[i] += *matrix_value(&r->weights, j, i);
    }
}

void
rbf_learning_with_fixed_centers(struct rbf *r,
                                const struct matrix *x,
                                const struct matrix *d)
{
    rbf_initialize_centers_at_random(r);
    rbf_compute_center_widths(r);
    rbf_compute_green(r, x);
    rbf_compute_weights(r, d);
}

void
rbf_learning_supervised(struct rbf *r,
                        const struct matrix *x,
                        const struct matrix *d)
{
    rbf_initialize_centers_at_random(r);

    /* TODO: write the rest of the algorthm. */
}

void
rbf_learning_self_organized(struct rbf *r,
                            const struct matrix *x,
                            const struct matrix *d)
{
    unsigned int i, j, s, k = 0;
    clann_real_type v, c[r->centers.cols], e = 0;

    rbf_initialize_centers_at_random(r);
    rbf_compute_center_widths(r);

    do
    {
        i = (int) clann_rand(0, x->rows - 1);

        for (j = 0; j < r->centers.cols; j++)
        {
            v = 0;

            for (s = 0; s < r->centers.rows; s++)
                v += CLANN_POW(*matrix_value(x, i, s) -
                               *matrix_value(&r->centers, s, j),
                               2);

            if (v < e || j == 0)
            {
                k = j;
                e = v;
            }
        }

        e = 0;

        for (s = 0; s < r->centers.rows; s++)
        {
            e += *matrix_value(&r->centers, s, k);

            v = *matrix_value(x, i, s) - *matrix_value(&r->centers, s, k);
            v = r->learning_rate_centers * v;
            *matrix_value(&r->centers, s, k) += v;

            e -= *matrix_value(&r->centers, s, k);
        }

        c[k] = CLANN_POW(e, 2);
        e = 0;

        for (s = 0; s < r->centers.cols; s++)
            e += c[s];

        e /= r->centers.cols;
    }
    while (e > r->noticeable_change_rate);

    rbf_compute_green(r, x);
    rbf_compute_weights(r, d);

    /**
     *
     */
    struct neuron n[r->output_size];
    struct lms l;

    lms_initialize(&l, r->learning_rate_weights);

    for (s = 0; s < r->output_size; s++)
    {
        neuron_initialize(&n[s], r->number_of_centers);

        for (i = 0; i < r->number_of_centers + 1; i++)
            n[s].weights[i] = *matrix_value(&r->weights, i, s);
    }

    do
    {
        e = 0;

        for (i = 0; i < r->number_of_inputs; i++)
        {
            for (j = 0; j < r->output_size; j++)
            {
                lms_learn(&n[j],
                          &l,
                          matrix_value(&r->green, i, 0),
                          matrix_value(d, j, 0));

                e += CLANN_POW(n[j].error, 2);
            }
        }

        e /= r->number_of_inputs;
    }
    while (e > r->desired_error);
}


void
rbf_compute_center_widths(struct rbf *r)
{
    unsigned int i, j, s;
    clann_real_type v, d_max = 0;

    for (i = 0; i < r->centers.cols; i++)
    {
        for (j = 0; j < r->centers.cols; j++)
        {
            v = 0;

            for (s = 0; s < r->centers.rows; s++)
                v += CLANN_POW(*matrix_value(&r->centers, s, i) -
                               *matrix_value(&r->centers, s, j),
                               2);

            v = sqrtl(v);

            if (v > d_max)
                d_max = v;
        }
    }

    v = d_max / sqrtl(2 * r->number_of_centers);

    for (i = 0; i < r->number_of_centers; i++)
        r->centers_width[i] = v;
}

void
rbf_initialize_centers_at_random(struct rbf *r)
{
    unsigned int i, j;

    for (i = 0; i < r->centers.cols; i++)
        for (j = 0; j < r->centers.rows; j++)
            *matrix_value(&r->centers, j, i) = clann_rand(-1, 1);
}
