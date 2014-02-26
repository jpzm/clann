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

#include "backprop.h"


void
backprop_adjust_weights(struct neuron *n,
                        const clann_real_type *y,
                        const clann_real_type *g,
                        clann_real_type momentum,
                        clann_real_type learing_rate)
{
    unsigned int i;

    for (i = 0; i < n->n_weights; i++)
    {
        n->weights[i] += momentum * n->old_weights[i];
        n->weights[i] += learing_rate * (*g) * y[i];
        n->old_weights[i] = learing_rate * (*g) * y[i];
    }

    n->weights[i] += momentum * n->old_weights[i];
    n->weights[i] += learing_rate * (*g);
    n->old_weights[i] = learing_rate * (*g);
}


void
backprop_learn(struct mlp *ann,
               const clann_real_type *x,
               const clann_real_type *d,
               clann_real_type momentum,
               clann_real_type learing_rate)
{
    mlp_forward_computation(ann, x);
    backprop_backward_computation(ann, x, d, momentum, learing_rate);
}


void
backprop_learn_epoch(struct mlp *ann,
                     const struct matrix *x,
                     const struct matrix *d,
                     clann_real_type momentum,
                     clann_real_type learing_rate)
{
    ann->error = 0;

    unsigned int i;
    for (i = 0; i < x->rows; i++)
    {
        backprop_learn(ann,
                       matrix_value(x, i, 0),
                       matrix_value(d, i, 0),
                       momentum,
                       learing_rate);

        mlp_compute_instantaneous_error(ann);
    }

    mlp_compute_avarage_error(ann, x->rows);
}

void
backprop_train(struct mlp *ann,
               const struct matrix *x,
               const struct matrix *d,
               clann_real_type momentum,
               clann_real_type learing_rate,
               clann_real_type desired_error,
               const unsigned int max_epochs)
{
    unsigned int e = 0;

    do
    {
        e++;

        backprop_learn_epoch(ann,
                             x,
                             d,
                             momentum,
                             learing_rate);

#if CLANN_VERBOSE
        if (e % 100 == 0 || e == 1)
            printf("N. [BACKPROP] Train error: " CLANN_PRINTF " (%d).\n",
                   ann->avarage_error,
                   e);
#endif
    }
    while ((!max_epochs || e < max_epochs) &&
           ann->avarage_error > desired_error);
}

void
backprop_train_with_validation(struct mlp *ann,
                               const struct matrix *tx,
                               const struct matrix *td,
                               const struct matrix *vx,
                               const struct matrix *vd,
                               clann_real_type momentum,
                               clann_real_type learing_rate,
                               clann_real_type desired_error,
                               const unsigned int max_epochs)
{
    unsigned int e = 0;
    clann_real_type train_error = 0;

    do
    {
        e++;

        backprop_learn_epoch(ann,
                             tx,
                             td,
                             momentum,
                             learing_rate);

        train_error = ann->avarage_error;

        mlp_validate_epoch(ann,
                           vx,
                           vd);

#if CLANN_VERBOSE
        if (e % 100 == 0 || e == 1)
            printf("N. [BACKPROP] Train error: " CLANN_PRINTF
                   ", validation error: " CLANN_PRINTF " (Epoch: %d).\n",
                   train_error,
                   ann->avarage_error,
                   e);
#endif
    }
    while ((!max_epochs || e < max_epochs) && train_error > desired_error);
}

void
backprop_backward_computation(struct mlp *ann,
                              const clann_real_type *x,
                              const clann_real_type *d,
                              clann_real_type momentum,
                              clann_real_type learing_rate)
{
    mlp_compute_output_error(ann, d);

    unsigned int l, j;
    for (l = ann->number_of_layers - 2; l > 0; l--)
    {
        for (j = 0; j < ann->layers[l].size; j++)
        {
            backprop_compute_gradient(ann, l, j, ann->layers[l - 1].output);

            backprop_adjust_weights(&ann->layers[l].neurons[j],
                                    ann->layers[l - 1].output,
                                    &ann->layers[l].gradients[j],
                                    momentum,
                                    learing_rate);
        }
    }

    for (j = 0; j < ann->layers[0].size; j++)
    {
        backprop_compute_gradient(ann, 0, j, x);

        backprop_adjust_weights(&ann->layers[0].neurons[j],
                                x,
                                &ann->layers[0].gradients[j],
                                momentum,
                                learing_rate);
    }
}

void
backprop_compute_gradient(struct mlp *ann,
                          const unsigned int l,
                          const unsigned int j,
                          const clann_real_type *x)
{
    struct neuron *n = &ann->layers[l].neurons[j];
    clann_real_type g = 0;

    if (l == ann->number_of_layers - 2)
        g = ann->layers[l].neurons[j].error;

    else
    {
        struct mlp_layer *next = &ann->layers[l + 1];

        unsigned int k;
        for (k = 0; k < next->size; k++)
            g += next->gradients[k] * next->neurons[k].weights[j];
    }
    
    switch (n->activation_function)
    {
        case FUNCTION_SIGMOID:
            g = g * n->output * (1 - n->output);
            break;

        case FUNCTION_HYPERBOLIC_TANGENT:
            g = g * (1 - n->output) * (1 + n->output);
            break;

        default:
            printf("E. [BACKPROP] Invalid activation function.\n");
            exit(EXIT_FAILURE);
    }

    ann->layers[l].gradients[j] = g;
}
