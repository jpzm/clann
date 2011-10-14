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
    struct matrix weights;
    clann_size_type number_of_neurons; // size of a memory
    clann_size_type number_of_memories;
};


/**
 * Initialize an given Hopfield network
 */
inline void
hopfield_initialize(struct hopfield *ann,
                    clann_size_type number_of_neurons,
                    clann_size_type number_of_memories);

/**
 * Finalize an given Hopfield network
 */
inline void
hopfield_finalize(struct hopfield *ann);

/**
 * Compute neuron output given a neuron and its input
 */
void
hopfield_train(struct hopfield *ann,
               struct matrix *memories);

#endif
