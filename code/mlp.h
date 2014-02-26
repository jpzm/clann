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

#ifndef MLP_H
#define MLP_H

#include <stdlib.h>
#include "clann.h"
#include "neuron.h"
#include "matrix.h"

/**
 * Layer structure
 */
struct mlp_layer
{
    unsigned int size;
    clann_real_type *output;
    clann_real_type *gradients;
    struct neuron *neurons;
};

/**
 * MLP structure
 */
struct mlp
{
    struct mlp_layer *layers;
    struct mlp_layer *output_layer;
    unsigned int *architecture;
    unsigned int number_of_layers;
    volatile clann_real_type error;
    volatile clann_real_type avarage_error;
};


/**
 * Initialize an given layer
 */
void
mlp_layer_initialize(struct mlp_layer *l,
                     const unsigned int input_size,
                     const unsigned int number_of_neurons);
/**
 * Finalize an given layer
 */
void
mlp_layer_finalize(struct mlp_layer *l);

/**
 *
 */
void
mlp_initialize(struct mlp *ann,
               unsigned int *architecture,
               const unsigned int number_of_layers);

/**
 *
 */
void
mlp_finalize(struct mlp *ann);

/**
 *
 */
void
mlp_forward_computation(struct mlp *ann,
                        const clann_real_type *x);

/**
 *
 */
void
mlp_compute_layer_output(struct mlp_layer *l,
                         const clann_real_type *x);

/**
 *
 */
void
mlp_compute_instantaneous_error(struct mlp *ann);

/**
 *
 */
void
mlp_compute_avarage_error(struct mlp *ann,
                          const unsigned int n);

/**
 *
 */
void
mlp_compute_output_error(struct mlp *ann,
                         const clann_real_type *d);

/**
 *
 */
void
mlp_validate(struct mlp *ann,
             const clann_real_type *x,
             const clann_real_type *d);

/**
 *
 */
void
mlp_validate_epoch(struct mlp *ann,
                   const struct matrix *x,
                   const struct matrix *d);

/**
 *
 */
void
mlp_fill(struct mlp *ann,
         const struct matrix *w,
         const struct matrix *f);

#endif
