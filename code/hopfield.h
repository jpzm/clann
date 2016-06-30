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

#ifndef HOPFIELD_H
#define HOPFIELD_H

#include <stdio.h>
#include <stdlib.h>
#include "clann.h"
#include "matrix.h"

/**
 * Hopfield basic structure
 */
struct hopfield
{
    clann_matrix_type weights;
    clann_size_type n_neurons;
    clann_size_type n_memories;
    clann_real_type *output;
};


/**
 * Initialize an given Hopfield network
 */
clann_void_type
hopfield_initialize(struct hopfield *ann,
                    clann_size_type n_neurons,
                    clann_size_type n_memories);

/**
 * Finalize an given Hopfield network
 */
clann_void_type
hopfield_finalize(struct hopfield *ann);

/**
 * 
 */
clann_void_type
hopfield_train(struct hopfield *ann,
               clann_matrix_type *memories);

/**
 * 
 */
clann_void_type
hopfield_compute_output(struct hopfield *ann,
                        clann_real_type *input);

/**
 * 
 */
clann_matrix_type *
hopfield_find_spurious_states(struct hopfield *ann);

#endif
