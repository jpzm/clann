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

#include "hopfield.h"


clann_void_type
hopfield_initialize(struct hopfield *ann,
                    clann_size_type n_neurons,
                    clann_size_type n_memories)
{
    clann_matrix_initialize(&ann->weights, n_neurons, n_memories);
    ann->n_neurons = n_neurons;
    ann->n_memories = n_memories;
    ann->output = malloc(sizeof(clann_real_type) * n_neurons);
}


clann_void_type
hopfield_finalize(struct hopfield *ann)
{
    clann_matrix_finalize(&ann->weights);

    free(ann->output);
}

clann_void_type
hopfield_train(struct hopfield *ann,
               clann_matrix_type *memories)
{
    // TODO: all of it.
}

clann_void_type
hopfield_compute_output(struct hopfield *ann,
                        clann_real_type *input)
{
    // TODO: all of it.
}

clann_matrix_type *
hopfield_find_spurious_states(struct hopfield *ann)
{
    // TODO: all of it.

    return NULL;
}
