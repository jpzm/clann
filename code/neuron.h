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

#ifndef NEURON_H
#define NEURON_H

#include <stdio.h>
#include <stdlib.h>
#include "clann.h"
#include "function.h"

/**
 * Neuron basic structure
 */
struct neuron
{
    volatile clann_real_type *weights;
    volatile clann_real_type *old_weights;
    volatile clann_real_type output;
    volatile clann_real_type error;
    unsigned int number_of_weights;
    unsigned int activation_function;
};


/**
 * Initialize an given neuron
 */
inline void
neuron_initialize(struct neuron *n,
                  const unsigned int number_of_weights);

/**
 * Initialize an given neuron
 */
inline void
neuron_finalize(struct neuron *n);

/**
 * Compute neuron output given a neuron and its input
 */
inline void
neuron_compute_output(struct neuron *n,
                      const clann_real_type *x);

#endif
