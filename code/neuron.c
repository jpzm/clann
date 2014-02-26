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

#include "neuron.h"


void
neuron_initialize(struct neuron *n,
                  const unsigned int n_weights)
{
    n->n_weights = n_weights;
    n->activation_function = FUNCTION_LINEAR;
    n->weights = malloc(sizeof(clann_real_type) * (n->n_weights + 1));
    n->old_weights = malloc(sizeof(clann_real_type) * (n->n_weights + 1));

    n->output = 0;
    n->error = 0;

    unsigned int i;
    for (i = 0; i <= n->n_weights; i++)
    {
        n->weights[i] = clann_rand(-1, 1);
        n->old_weights[i] = 0;
    }
}

void
neuron_finalize(struct neuron *n)
{
    free((void *) n->weights);
    free((void *) n->old_weights);

    n->n_weights = 0;
}

void
neuron_compute_output(struct neuron *n,
                      const clann_real_type *x)
{
    clann_real_type sum = 0;

    unsigned int i;
    for (i = 0; i < n->n_weights; i++)
        sum += n->weights[i] * x[i];

    sum += n->weights[i] * 1.0;

    switch (n->activation_function)
    {
        case FUNCTION_LINEAR:
            n->output = sum;
            break;

        case FUNCTION_STEP:
            n->output = function_step(sum);
            break;

        case FUNCTION_SIGNAL:
            n->output = function_signal(sum);
            break;

        case FUNCTION_SIGMOID:
            n->output = function_sigmoid(sum);
            break;

        case FUNCTION_HYPERBOLIC_TANGENT:
            n->output = function_tanh(sum);
            break;

        default:
            printf("E. [NEURON] Invalid activation function.\n");
            exit(EXIT_FAILURE);
    }

    if (isnan(n->output))
    {
        perror("Divergence error");
        exit(EXIT_FAILURE);
    }
}
