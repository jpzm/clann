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

#include "ilpso.h"


clann_void_type
ilpso_initialize(struct ilpso *s,
                 clann_void_type *problem,
                 const unsigned int particle_length)
{
    s->number_of_particles = 10;

    clann_matrix_initialize(&s->positions,
                            s->number_of_particles,
                            particle_length);
    clann_matrix_initialize(&s->velocities,
                            s->number_of_particles,
                            particle_length);
    clann_matrix_initialize(&s->best_positions,
                            s->number_of_particles,
                            particle_length);

    s->rand_max = 1;
    s->rand_min = 0;

    s->problem = problem;
    s->f_constraint = NULL;
    s->f_fitness = NULL;

    s->fitness = malloc(sizeof(clann_real_type) * s->number_of_particles);
    s->solution = malloc(sizeof(clann_real_type) * particle_length);

    s->velocity_reduction_limit = 1e-5;
    s->velocity_reduction_factor = 0.9;

    s->particle_length = particle_length;
    s->desired_variance = 0.2;
    s->constriction_factor = 0.73;
    s->mutation_probability = 0.3;
    s->velocity_limits[0] = -4;
    s->velocity_limits[1] =  4;
    s->acceleration_coefficients[0] = 2.05;
    s->acceleration_coefficients[1] = 2.05;
}

clann_void_type
ilpso_finalize(struct ilpso* s)
{
    clann_matrix_finalize(&s->positions);
    clann_matrix_finalize(&s->velocities);
    clann_matrix_finalize(&s->best_positions);

    free((clann_void_type *) s->fitness);
    free((clann_void_type *) s->solution);
}

clann_void_type
ilpso_run(struct ilpso *s,
          const unsigned int max_iterations,
          const clann_real_type noticeable_change_rate)
{
    unsigned int iteration = 1,
                 change_count = 0,
                 i,
                 j,
                 c;
    clann_real_type v,
               w,
               r1,
               r2,
               *reference,
               best_fitness,
               local_best_fitness,
               avarage[s->particle_length],
               delta = noticeable_change_rate + 1;

    ilpso_initialize_positions_and_velocities(s);

    for (i = 0; i < s->number_of_particles; i++)
    {
        s->f_constraint(s->problem,
                        clann_matrix_value(&s->positions, i, 0));
        s->fitness[i] = s->f_fitness(s->problem,
                                     clann_matrix_value(&s->positions, i, 0));
    }

    for (i = 0; i < s->particle_length; i++)
        s->solution[i] = *clann_matrix_value(&s->positions, 0, i);

    s->last_best = clann_matrix_value(&s->positions, 0, 0);
    best_fitness = s->f_fitness(s->problem, s->solution);
    local_best_fitness = best_fitness;

    while (iteration <= max_iterations &&
           change_count < noticeable_change_rate)
    {
        delta = best_fitness;

        for (i = 0; i < s->number_of_particles; i++)
        {
            /**
             *
             */
            v = s->f_fitness(s->problem,
                             clann_matrix_value(&s->best_positions, i, 0));

            if (s->fitness[i] > v)
                for (c = 0; c < s->particle_length; c++)
                {
                    v = *clann_matrix_value(&s->positions, i, c);
                    *clann_matrix_value(&s->best_positions, i, c) = v;
                }

            /**
             *
             */
            r1 = clann_nrand();
            r2 = clann_nrand();

            if (clann_nrand() > iteration / (max_iterations))
            {
                c = 0;

                for (j = 0; j < s->particle_length; j++)
                    avarage[j] = 0;

                while (c++ < (s->number_of_particles / 5))
                {
                    v = (int) clann_rand(0, s->number_of_particles - 1);

                    for (j = 0; j < s->particle_length; j++)
                        avarage[j] += *clann_matrix_value(&s->positions, v, j) / 5;
                }

                reference = avarage;
            }
            else
                reference = s->last_best;

            for (j = 0; j < s->particle_length; j++)
            {
                v = *clann_matrix_value(&s->velocities, i, j);

                w = *clann_matrix_value(&s->best_positions, i, j);
                w = w - *clann_matrix_value(&s->positions, i, j);
                v += s->acceleration_coefficients[0] * r1 * w;

                w = reference[j] - *clann_matrix_value(&s->positions, i, j);
                v += s->acceleration_coefficients[1] * r2 * w;

                v *= s->constriction_factor;

                if (v < s->velocity_limits[0])
                   v = s->velocity_limits[0];

                if (v > s->velocity_limits[1])
                   v = s->velocity_limits[1];

                *clann_matrix_value(&s->velocities, i, j) = v;
                *clann_matrix_value(&s->positions, i, j) += v;
            }

            s->f_constraint(s->problem,
                            clann_matrix_value(&s->positions, i, 0));

            s->fitness[i] = s->f_fitness(s->problem,
                                         clann_matrix_value(&s->positions, i, 0));

            local_best_fitness = s->f_fitness(s->problem, s->positions.values);

            if (s->fitness[i] > local_best_fitness)
            {
                if (s->fitness[i] > best_fitness)
                {
                    for (c = 0; c < s->particle_length; c++)
                        s->solution[c] = *clann_matrix_value(&s->positions, i, c);

                    best_fitness = s->fitness[i];
                }

                local_best_fitness = s->fitness[i];
                s->last_best = clann_matrix_value(&s->positions, i, 0);
            }
        }

        /**
         *
         */
        if (ilpso_compute_probability_of_mutation(s) > clann_nrand())
        {
            c = 0;

            while (c < s->number_of_particles / 5)
            {
                i = (int) clann_rand(0, s->number_of_particles - 1);

                if (clann_matrix_value(&s->positions, i, 0) != s->last_best)
                {
                    c++;

                    for (j = 0; j < s->particle_length; j++)
                    {
                        w = clann_rand(s->rand_min, s->rand_max);
                        *clann_matrix_value(&s->positions, i, j) = w;
                    }

                    s->f_constraint(s->problem,
                                    clann_matrix_value(&s->positions, i, 0));

                    w = s->f_fitness(s->problem,
                                     clann_matrix_value(&s->positions, i, 0));

                    s->fitness[i] = w;
                }

                if (s->fitness[i] > local_best_fitness)
                {
                    if (s->fitness[i] > best_fitness)
                    {
                        for (j = 0; j < s->particle_length; j++)
                            s->solution[j] = *clann_matrix_value(&s->positions, i, j);

                        best_fitness = s->fitness[i];
                    }

                    local_best_fitness = s->fitness[i];
                    s->last_best = clann_matrix_value(&s->positions, i, 0);
                }
            }
        }

        delta = best_fitness - delta;

        if (delta != 0 || iteration == 1)
        {
#if CLANN_VERBOSE
            printf("N. [ILPSO] Fitness: " CLANN_PRINTF ", from: %p "
                   "(Generation: %d).\n",
                   best_fitness,
                   s->last_best,
                   iteration);
#endif
            if (delta != 0)
                change_count = 0;
        }
        else
        {
            change_count++;

            if ((change_count % 10) == 0)
            {
                if (s->velocity_limits[0] > s->velocity_reduction_limit)
                    s->velocity_limits[0] *= s->velocity_reduction_factor;

                if (s->velocity_limits[1] > s->velocity_reduction_limit)
                    s->velocity_limits[1] *= s->velocity_reduction_factor;
            }
        }

        iteration++;
    }
}

clann_void_type
ilpso_initialize_positions_and_velocities(struct ilpso *s)
{
    unsigned int i, j;
    clann_real_type v;

    for (i = 0; i < s->number_of_particles; i++)
        for (j = 0; j < s->particle_length; j++)
        {
            v = clann_rand(s->rand_min, s->rand_max);

            *clann_matrix_value(&s->positions, i, j) = v;
            *clann_matrix_value(&s->velocities, i, j) = 0;
            *clann_matrix_value(&s->best_positions, i, j) = v;
        }
}

clann_real_type
ilpso_compute_probability_of_mutation(struct ilpso *s)
{
    clann_real_type v = 0,
               f_avg = 0,
               f_max = 0,
               f[s->number_of_particles];
    unsigned int i;

    for (i = 0; i < s->number_of_particles; i++)
    {
        f[i] = s->f_fitness(s->problem,
                            clann_matrix_value(&s->positions, i, 0));
        f_avg += f[i];
    }

    f_avg /= s->number_of_particles;

    for (i = 0; i < s->number_of_particles; i++)
        f_max = (abs(f[i] - f_avg) > f_max) ? abs(f[i] - f_avg) : 1;

    for (i = 0; i < s->number_of_particles; i++)
        v += CLANN_POW((f[i] - f_avg) / f_max, 2);

    return v / s->number_of_particles;
}
