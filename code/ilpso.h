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

#ifndef ILPSO_H
#define ILPSO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "clann.h"
#include "matrix.h"

#define ILPSO_DEFAULT_MAXITERATIONS             5000
#define ILPSO_DEFAULT_NOCHANGE_ITERATIONS       500


struct ilpso
{
    void *problem;
    void (*f_constraint)(void *, clann_real_type *);
    clann_real_type (*f_fitness)(void *, clann_real_type *);

    unsigned int particle_length;
    unsigned int number_of_particles;

    struct matrix positions;
    struct matrix velocities;
    struct matrix best_positions;

    clann_real_type rand_max;
    clann_real_type rand_min;

    clann_real_type *fitness;
    clann_real_type *solution;
    clann_real_type *last_best;
    clann_real_type desired_variance;
    clann_real_type constriction_factor;
    clann_real_type mutation_probability;
    clann_real_type velocity_limits[2];
    clann_real_type velocity_reduction_limit;
    clann_real_type velocity_reduction_factor;
    clann_real_type acceleration_coefficients[2];
};


/**
 *
 */
inline void
ilpso_initialize(struct ilpso *s,
                 void *problem,
                 const unsigned int particle_length);

/**
 *
 */
inline void
ilpso_finalize(struct ilpso *s);

/**
 *
 */
inline void
ilpso_run(struct ilpso *s,
          const unsigned int max_iterations,
          const clann_real_type noticeable_change_rate);

/**
 *
 */
inline void
ilpso_initialize_positions_and_velocities(struct ilpso *s);

/**
 *
 */
inline clann_real_type
ilpso_compute_probability_of_mutation(struct ilpso *s);

#endif
