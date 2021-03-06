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

#ifndef BACKPROP_H
#define BACKPROP_H

#include <stdio.h>
#include <stdlib.h>
#include "clann.h"
#include "matrix.h"
#include "mlp.h"


/**
 * Adjust weights function
 */
clann_void_type
backprop_adjust_weights(struct neuron *n,
                        const clann_real_type *y,
                        const clann_real_type *g,
                        clann_real_type momentum,
                        clann_real_type learing_rate);

/**
 *
 */
clann_void_type
backprop_learn(struct mlp *ann,
               const clann_real_type *x,
               const clann_real_type *d,
               clann_real_type momentum,
               clann_real_type learing_rate);

/**
 *
 */
clann_void_type
backprop_learn_epoch(struct mlp *ann,
                     const clann_matrix_type *x,
                     const clann_matrix_type *d,
                     clann_real_type momentum,
                     clann_real_type learing_rate);

/**
 *
 */
clann_void_type
backprop_train(struct mlp *ann,
               const clann_matrix_type *x,
               const clann_matrix_type *d,
               clann_real_type momentum,
               clann_real_type learing_rate,
               clann_real_type desired_error,
               const unsigned int max_epochs);

/**
 *
 */
clann_void_type
backprop_train_with_validation(struct mlp *ann,
                               const clann_matrix_type *tx,
                               const clann_matrix_type *td,
                               const clann_matrix_type *vx,
                               const clann_matrix_type *vd,
                               clann_real_type momentum,
                               clann_real_type learing_rate,
                               clann_real_type desired_error,
                               const unsigned int max_epochs);

/**
 *
 */
clann_void_type
backprop_backward_computation(struct mlp *ann,
                              const clann_real_type *x,
                              const clann_real_type *d,
                              clann_real_type momentum,
                              clann_real_type learing_rate);

/**
 *
 */
clann_void_type
backprop_compute_gradient(struct mlp *ann,
                          const unsigned int l,
                          const unsigned int j,
                          const clann_real_type *x);

#endif
