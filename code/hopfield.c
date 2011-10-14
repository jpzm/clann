/**
 * Copyright (C) 2011 Joao Paulo de Souza Medeiros
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

#include "hopfield.h"


void
hopfield_initialize(struct hopfield *ann,
                    clann_size_type number_of_neurons,
                    clann_size_type number_of_memories)
{
    matrix_initialize(&ann->weights, number_of_neurons, number_of_memories);
    ann->number_of_neurons = number_of_neurons;
    ann->number_of_memories = number_of_memories;
}


void
hopfield_finalize(struct hopfield *ann)
{
    matrix_finalize(&ann->weights);
}

void
hopfield_train(struct hopfield *ann,
               struct matrix *memories)
{
    // TODO: all of it.
}
