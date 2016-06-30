/**
 * Copyright (C) 2008-2014 Joao Paulo de Souza Medeiros
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

#ifndef FMDP_H
#define FMDP_H

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "io.h"
#include "clann.h"


/**
 * Finite Markov Decision Process
 */
struct fmdp
{
    clann_matrix_type policy;
    clann_matrix_type state_value;
    clann_matrix_type action_value;

    clann_real_type (*f_returns)(struct fmdp *,
                                 clann_real_type,
                                 clann_real_type,
                                 clann_real_type);
    clann_real_type (*f_probabilities)(struct fmdp *,
                                       clann_real_type,
                                       clann_real_type,
                                       clann_real_type);

    clann_real_type *states;
    clann_real_type *actions;
    clann_real_type discount_rate;

    unsigned int number_of_states;
    unsigned int number_of_actions;
};


/**
 *
 */
clann_void_type
fmdp_initialize(struct fmdp *mdp,
                clann_real_type discount_rate,
                unsigned int number_of_states,
                unsigned int number_of_actions);

/**
 *
 */
clann_void_type
fmdp_finalize(struct fmdp *mdp);

/**
 *
 */
int
fmdp_save(struct fmdp *mdp,
          const char *file);

/**
 *
 */
int
fmdp_open(struct fmdp *mdp,
          const char *file);

#endif
