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

#ifndef RBF_H
#define RBF_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "clann.h"
#include "function.h"
#include "kmeans.h"
#include "matrix.h"
#include "metric.h"
#include "neuron.h"
#include "lms.h"

#define RBF_LEARNING_FIXED          0
#define RBF_LEARNING_SUPERVISED     1
#define RBF_LEARNING_SELF_ORGANIZED 2
#define RBF_LEARNING_SVM            3


/**
 * RBF structure
 */
struct rbf
{
    struct matrix green;
    struct matrix centers;
    struct matrix weights;
    clann_size_type n_inputs;
    clann_size_type n_centers;
    clann_size_type input_size;
    clann_size_type output_size;
    unsigned int green_function;
    unsigned int learning_strategy;
    clann_real_type *output;
    clann_real_type *centers_width;
    clann_real_type desired_error;
    clann_real_type learning_rate_centers;
    clann_real_type learning_rate_weights;
    clann_real_type learning_rate_spreads;
    clann_real_type noticeable_change_rate;
};


/**
 * Initialize an given RBF
 */
void
rbf_initialize(struct rbf *ann,
               clann_size_type input_size,
               clann_size_type output_size,
               clann_size_type n_inputs,
               clann_size_type n_centers);
/**
 *
 */
void
rbf_finalize(struct rbf *ann);

/**
 *
 */
void
rbf_learn(struct rbf *ann,
          const struct matrix *x,
          const struct matrix *d);

/**
 *
 */
void
rbf_learning_with_fixed_centers(struct rbf *ann,
                                const struct matrix *x,
                                const struct matrix *d);

/**
 *
 */
void
rbf_learning_supervised(struct rbf *ann,
                        const struct matrix *x,
                        const struct matrix *d);

/**
 *
 */
void
rbf_learning_self_organized(struct rbf *ann,
                            const struct matrix *x,
                            const struct matrix *d);

/**
 *
 */
void
rbf_compute_green(struct rbf *ann,
                  const struct matrix *x);

/**
 *
 */
void
rbf_compute_weights(struct rbf *ann,
                    const struct matrix *d);

/**
 *
 */
void
rbf_compute_output(struct rbf *ann,
                   clann_real_type *x);

/**
 *
 */
void
rbf_initialize_centers_at_random(struct rbf *ann,
                                 const struct matrix *x);

/**
 *
 */
void
rbf_compute_center_widths(struct rbf *ann);

#endif
