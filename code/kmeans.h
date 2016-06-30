/**
 * Copyright (C) 2011-2014 Joao Paulo de Souza Medeiros
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

#ifndef KMEANS_H
#define KMEANS_H

#include <stdlib.h>
#include "clann.h"
#include "matrix.h"
#include "metric.h"


/**
 * K-means structure
 */
struct kmeans
{
    clann_size_type n_centers;
    clann_real_type noticeable_change_rate;
    clann_matrix_type centers;
    clann_matrix_type *old_centers;
    clann_size_type center_size;
};


/**
 * Initialize a K-means structure
 */
clann_void_type
kmeans_initialize(struct kmeans *ann,
                  clann_size_type n_centers,
                  clann_size_type center_size,
                  clann_real_type noticeable_change_rate);

/**
 * Finalize a K-means structure
 */
clann_void_type
kmeans_finalize(struct kmeans *ann);

/**
 * K-means train function
 */
clann_void_type
kmeans_train(struct kmeans *ann,
             const clann_matrix_type *x,
             clann_real_type learning_rate);

#endif
