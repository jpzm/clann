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

#ifndef RBF_H
#define RBF_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "clann.h"
#include "function.h"
#include "matrix.h"
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
    unsigned int number_of_inputs;
    unsigned int number_of_centers;
    unsigned int input_size;
    unsigned int output_size;
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
inline void
rbf_initialize(struct rbf *r,
               const unsigned int input_size,
               const unsigned int output_size,
               const unsigned int number_of_inputs,
               const unsigned int number_of_centers);
/**
 *
 */
inline void
rbf_finalize(struct rbf *r);

/**
 *
 */
inline void
rbf_learn(struct rbf *r,
          const struct matrix *x,
          const struct matrix *d);

/**
 *
 */
inline void
rbf_learning_with_fixed_centers(struct rbf *r,
                                const struct matrix *x,
                                const struct matrix *d);

/**
 *
 */
inline void
rbf_learning_supervised(struct rbf *r,
                        const struct matrix *x,
                        const struct matrix *d);

/**
 *
 */
inline void
rbf_learning_self_organized(struct rbf *r,
                            const struct matrix *x,
                            const struct matrix *d);

/**
 *
 */
inline void
rbf_compute_green(struct rbf *r,
                  const struct matrix *x);

/**
 *
 */
inline void
rbf_compute_weights(struct rbf *r,
                    const struct matrix *d);

/**
 *
 */
inline void
rbf_compute_output(struct rbf *r,
                   const clann_real_type *x);

/**
 *
 */
inline void
rbf_initialize_centers_at_random(struct rbf *r);

/**
 *
 */
inline void
rbf_compute_center_widths(struct rbf *r);

#endif
