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
inline void
backprop_adjust_weights(struct neuron *n,
                        const clann_real_type *y,
                        const clann_real_type *g,
                        clann_real_type momentum,
                        clann_real_type learing_rate);

/**
 *
 */
inline void
backprop_learn(struct mlp *ann,
               const clann_real_type *x,
               const clann_real_type *d,
               clann_real_type momentum,
               clann_real_type learing_rate);

/**
 *
 */
inline void
backprop_learn_epoch(struct mlp *ann,
                     const struct matrix *x,
                     const struct matrix *d,
                     clann_real_type momentum,
                     clann_real_type learing_rate);

/**
 *
 */
void
backprop_train(struct mlp *ann,
               const struct matrix *x,
               const struct matrix *d,
               clann_real_type momentum,
               clann_real_type learing_rate,
               clann_real_type desired_error,
               const unsigned int max_epochs);

/**
 *
 */
void
backprop_train_with_validation(struct mlp *ann,
                               const struct matrix *tx,
                               const struct matrix *td,
                               const struct matrix *vx,
                               const struct matrix *vd,
                               clann_real_type momentum,
                               clann_real_type learing_rate,
                               clann_real_type desired_error,
                               const unsigned int max_epochs);

/**
 *
 */
inline void
backprop_backward_computation(struct mlp *ann,
                              const clann_real_type *x,
                              const clann_real_type *d,
                              clann_real_type momentum,
                              clann_real_type learing_rate);

/**
 *
 */
inline void
backprop_compute_gradient(struct mlp *ann,
                          const unsigned int l,
                          const unsigned int j,
                          const clann_real_type *x);

#endif
