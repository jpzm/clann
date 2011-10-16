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

#include "perceptron.h"


void
perceptron_adjust_weights(struct neuron *n,
                          const clann_real_type *x,
                          const clann_real_type *d,
                          const clann_real_type learing_rate)
{
    n->error = *d - n->output;
#if CLANN_VERBOSE
    printf("N. [PERCEPTRON] Error: " CLANN_PRINTF ".\n", n->error);
#endif

    unsigned int i;
    for (i = 0; i < n->n_weights; i++)
        n->weights[i] += learing_rate * n->error * x[i];

    n->weights[i] += learing_rate * n->error * 1.0;
}


void
perceptron_learn(struct neuron *n,
                 const clann_real_type *x,
                 const clann_real_type *d,
                 const clann_real_type learing_rate)
{
    neuron_compute_output(n, x);
    perceptron_adjust_weights(n, x, d, learing_rate);
}


void
perceptron_learn_set(struct neuron *n,
                     const struct matrix *x,
                     const struct matrix *d,
                     const clann_real_type learing_rate,
                     const unsigned int number_of_epochs)
{
    unsigned int i, e = 0;

    while (e < number_of_epochs)
    {
        for (i = 0; i < x->rows; i++)
            perceptron_learn(n,
                             matrix_value(x, i, 0),
                             matrix_value(d, i, 0),
                             learing_rate);

        e++;
    }
}
