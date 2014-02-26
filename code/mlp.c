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

#include "mlp.h"


void
mlp_layer_initialize(struct mlp_layer *l,
                     const unsigned int input_size,
                     const unsigned int number_of_neurons)
{
    l->size = number_of_neurons;
    l->output = malloc(sizeof(clann_real_type) * number_of_neurons);
    l->gradients = malloc(sizeof(clann_real_type) * number_of_neurons);
    l->neurons = malloc(sizeof(struct neuron) * number_of_neurons);

    unsigned int i;
    for (i = 0; i < number_of_neurons; i++)
    {
        neuron_initialize(&l->neurons[i], input_size);
        l->neurons[i].activation_function = FUNCTION_HYPERBOLIC_TANGENT;

        l->output[i] = 0;
        l->gradients[i] = 0;
    }
}

void
mlp_layer_finalize(struct mlp_layer *l)
{
    unsigned int i;
    for (i = 0; i < l->size; i++)
        neuron_finalize(&l->neurons[i]);

    free((void *) l->neurons);
    free((void *) l->gradients);

    l->size = 0;
}

void
mlp_initialize(struct mlp *ann,
               unsigned int *architecture,
               const unsigned int number_of_layers)
{
    ann->layers = malloc(sizeof(struct mlp_layer) * (number_of_layers - 1));
    ann->number_of_layers = number_of_layers;
    ann->architecture = architecture;

    ann->avarage_error = 0;
    ann->error = 0;

    unsigned int i;
    for (i = 1; i < ann->number_of_layers; i++)
    {
        mlp_layer_initialize(&ann->layers[i - 1],
                             ann->architecture[i - 1],
                             ann->architecture[i]);
    }

    ann->output_layer = &ann->layers[number_of_layers - 2];
}

void
mlp_finalize(struct mlp *ann)
{
    unsigned int i;
    for (i = 0; i < ann->number_of_layers - 1; i++)
        mlp_layer_finalize(&ann->layers[i]);

    free((void *) ann->layers);

    ann->number_of_layers = 0;
    ann->architecture = (unsigned int *) NULL;
}

void
mlp_forward_computation(struct mlp *ann,
                        const clann_real_type *x)
{
    if (ann->number_of_layers > 1)
    {
        mlp_compute_layer_output(&ann->layers[0], x);

        unsigned int l;
        for (l = 1; l < ann->number_of_layers - 1; l++)
            mlp_compute_layer_output(&ann->layers[l],
                                     ann->layers[l - 1].output);
    }
}

void
mlp_compute_layer_output(struct mlp_layer *l,
                         const clann_real_type *x)
{
    unsigned int i;

    for (i = 0; i < l->size; i++)
    {
        neuron_compute_output(&l->neurons[i], x);
        l->output[i] = l->neurons[i].output;
    }
}

void
mlp_compute_instantaneous_error(struct mlp *ann)
{
    clann_real_type error = 0;
    unsigned int i;

    for (i = 0; i < ann->output_layer->size; i++)
        error += CLANN_POW(ann->output_layer->neurons[i].error, 2);

    ann->error += error / 2;
}

void
mlp_compute_avarage_error(struct mlp *ann,
                          const unsigned int n)
{
    ann->avarage_error = ann->error / n;
}

void
mlp_compute_output_error(struct mlp *ann,
                         const clann_real_type *d)
{
    struct neuron *n;

    unsigned int i;
    for (i = 0; i < ann->output_layer->size; i++)
    {
        n = &ann->output_layer->neurons[i];
        n->error = d[i] - n->output;
    }
}

void
mlp_validate(struct mlp *ann,
             const clann_real_type *x,
             const clann_real_type *d)
{
    mlp_forward_computation(ann, x);
    mlp_compute_output_error(ann, d);
}


void
mlp_validate_epoch(struct mlp *ann,
                   const struct matrix *x,
                   const struct matrix *d)
{
    unsigned int i;

    ann->error = 0;

    for (i = 0; i < x->rows; i++)
    {
        mlp_validate(ann,
                     matrix_value(x, i, 0),
                     matrix_value(d, i, 0));

        mlp_compute_instantaneous_error(ann);
    }

    mlp_compute_avarage_error(ann, x->rows);
}


void
mlp_fill(struct mlp *ann,
         const struct matrix *w,
         const struct matrix *f)
{
    unsigned int i, j, k, c = 0, p = 0;
    struct mlp_layer *l;

    for (i = 0; i < ann->number_of_layers - 1; i++)
    {
        l = &ann->layers[i];

        for (j = 0; j < l->size; j++)
        {
            for (k = 0; k <= l->neurons[j].n_weights; k++)
                l->neurons[j].weights[k] = w->values[p + k];

            l->neurons[j].activation_function = (unsigned int) f->values[c];
            c++;
            p += k;
        }
    }
}
