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

#ifndef SVM_H
#define SVM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "clann.h"
#include "rbf.h"
#include "mlp.h"
#include "function.h"
#include "matrix.h"
#include "ilpso.h"


#define SVM_SOLVE_BY_ILPSO          0

#define SVM_TYPE_RBF                0
#define SVM_TYPE_MLP                1
#define SVM_TYPE_POLY               2

#define SVM_SUPPORT_VECTOR_LIMIT    1e-7


/**
 * SVM structure
 */
struct svm
{
    unsigned int optimization_method;
    unsigned int kernel_type;
    unsigned int input_size;
    unsigned int number_of_inputs;
    unsigned int number_of_support_vectors;

    const struct matrix *x_set;
    const struct matrix *d_set;

    clann_real_type output;
    clann_real_type *weights;
    clann_real_type *multipliers;
    clann_real_type **support_vectors;
    clann_real_type punishment_factor;

    clann_real_type rbf_width;
    clann_real_type mlp_kappa;
    clann_real_type mlp_vartheta;
    clann_real_type poly_order;

    void *network;
};


/**
 * Initialize an given SVM
 */
inline void
svm_initialize(struct svm *s,
               const unsigned int input_size,
               const unsigned int number_of_inputs);

/**
 *
 */
inline void
svm_compute_weights(struct svm *s,
                    const struct matrix *x,
                    const struct matrix *d);

/**
 *
 */
inline void
svm_compute_output(struct svm *s,
                   const clann_real_type *x);

/**
 *
 */
inline clann_real_type
svm_compute_fitness_function(struct svm *s,
                             const clann_real_type *l);

/**
 *
 */
inline void
svm_constraint_function(struct svm *s,
                        clann_real_type *l);

/**
 *
 */
inline void
svm_solve_by_ilpso(struct svm *s,
                   clann_real_type *l);

/**
 *
 */
inline clann_real_type
svm_compute_kernel(struct svm *s,
                   const clann_real_type *a,
                   const clann_real_type *b);

#endif
