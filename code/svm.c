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

#include "svm.h"


clann_void_type
svm_initialize(struct svm *s,
               const unsigned int input_size,
               const unsigned int number_of_inputs)
{
    s->optimization_method = SVM_SOLVE_BY_ILPSO;
    s->kernel_type = SVM_TYPE_RBF;
    s->input_size = input_size;
    s->number_of_inputs = number_of_inputs;
    s->punishment_factor = 2.5;

    s->rbf_width = 1.0;

    s->mlp_kappa = 1.0;
    s->mlp_vartheta = -1.0;

    s->poly_order = 3;

    s->network = (clann_void_type *)NULL;
}

clann_void_type
svm_compute_weights(struct svm *s,
                    const clann_matrix_type *x,
                    const clann_matrix_type *d)
{
    clann_real_type *reference, multipliers[s->number_of_inputs];
    unsigned int i, j, total;

    s->x_set = x;
    s->d_set = d;

    s->number_of_support_vectors = 0;

    switch (s->optimization_method)
    {
        case SVM_SOLVE_BY_ILPSO:

            svm_solve_by_ilpso(s, multipliers);
            s->multipliers = multipliers;

            break;

        default:
            printf("E. [SVM] Invalid optimization method.\n");
            exit(EXIT_FAILURE);
    }

    /**
     * Computing support vectors
     */
    for (i = 0; i < s->number_of_inputs; i++)
        if (s->multipliers[i] > SVM_SUPPORT_VECTOR_LIMIT)
        {
            total = sizeof(clann_real_type *) * (s->number_of_support_vectors + 1);
            s->support_vectors = realloc(s->support_vectors, total);

            reference = clann_matrix_value(s->x_set, i, 0);
            s->support_vectors[s->number_of_support_vectors] = reference;

            s->number_of_support_vectors++;
        }

#if CLANN_VERBOSE
    printf("N. [SVM] Solution fitness: " CLANN_PRINTF ".\n",
           svm_compute_fitness_function(s, s->multipliers));

    printf("N. [SVM] Number of support vectors: %d (of %d).\n",
           s->number_of_support_vectors,
           s->number_of_inputs);
#endif

    /**
     *
     */
    if (s->kernel_type == SVM_TYPE_RBF || s->kernel_type == SVM_TYPE_MLP)
    {
        /**
         * Computing weights values
         */
        s->weights = malloc(sizeof(clann_real_type) *
                            s->number_of_support_vectors);

        for (i = 0; i < s->number_of_support_vectors; i++)
        {
            s->weights[i] = 0;

            for (j = 0; j < s->number_of_inputs; j++)
            {
                reference = clann_matrix_value(s->x_set, j, 0);

                s->weights[i] += s->multipliers[j];
                s->weights[i] *= *clann_matrix_value(s->d_set, j, 0);
                s->weights[i] *= svm_compute_kernel(s,
                                                    reference,
                                                    s->support_vectors[i]);
            }
        }

        /**
         * Creating neural network
         */
        if (s->kernel_type == SVM_TYPE_RBF)
        {
            /*struct rbf r;

            rbf_create(&r,
                       s->input_size,
                       1,
                       s->number_of_support_vectors,
                       s->support_vectors,
                       s->weights);

            s->network = (clann_void_type *) r;*/
        }
        else
        {
            // TODO: create two-layers MLP network
        }
    }
    else if (s->kernel_type == SVM_TYPE_POLY)
    {
        // TODO: Write polynomial algorithm.
    }
    else
    {
        printf("E. [SVM] Invalid kernel type.\n");
        exit(EXIT_FAILURE);
    }
}

clann_void_type
svm_compute_output(struct svm *s,
                   const clann_real_type *x)
{
    switch(s->kernel_type)
    {
        case SVM_TYPE_RBF:
            break;

        case SVM_TYPE_MLP:
            break;

        case SVM_TYPE_POLY:
            // TODO: Write polynomial algorithm.
            break;

        default:
            printf("E. [SVM] Invalid kernel type.\n");
            exit(EXIT_FAILURE);
    }
}

clann_void_type
svm_solve_by_ilpso(struct svm *s,
                   clann_real_type *l)
{
    struct ilpso pso;
    unsigned int i;

    ilpso_initialize(&pso, (clann_void_type *) s, s->number_of_inputs);

    pso.rand_max = s->punishment_factor;
    pso.f_fitness = (clann_void_type *) &svm_compute_fitness_function;
    pso.f_constraint = (clann_void_type *) &svm_constraint_function;

    ilpso_run(&pso,
              ILPSO_DEFAULT_MAXITERATIONS,
              ILPSO_DEFAULT_NOCHANGE_ITERATIONS);

    for (i = 0; i < s->number_of_inputs; i++)
        l[i] = pso.solution[i];

    ilpso_finalize(&pso);
}

clann_real_type
svm_compute_fitness_function(struct svm *s,
                             const clann_real_type *l)
{
    unsigned int i, j;
    clann_real_type v,
               t1 = 0,
               t2 = 0;

    for (i = 0; i < s->number_of_inputs; i++)
        t1 += l[i];

    for (i = 0; i < s->number_of_inputs; i++)
        for (j = 0; j < s->number_of_inputs; j++)
        {
            v = svm_compute_kernel(s,
                                   clann_matrix_value(s->x_set, i, 0),
                                   clann_matrix_value(s->x_set, j, 0));

            t2 += l[i] * l[j] * s->d_set->values[i] * s->d_set->values[j] * v;
        }

    return t1 - t2 / 2;
}

clann_void_type
svm_constraint_function(struct svm *s,
                        clann_real_type *l)
{
    clann_real_type c[s->number_of_inputs],
               c_sum = 0,
               error = 0;
    unsigned int i;

    /**
     * subject to restriction: 0 <= a <= C
     */
    for (i = 0; i < s->number_of_inputs; i++)
    {
        if (l[i] < 0)
            l[i] = 0;

        else if (l[i] > s->punishment_factor)
            l[i] = s->punishment_factor;
    }

    /**
     * compute error for subject: sum(a_i * d_i) = 0
     */
    for (i = 0; i < s->number_of_inputs; i++)
        error += l[i] * s->d_set->values[i];

    /**
     * adjust values
     */
    if (error != 0)
    {
        for (i = 0; i < s->number_of_inputs; i++)
        {
            if (error > 0)
            {
                if (s->d_set->values[i] < 0)
                    c[i] = s->punishment_factor - l[i];
                else
                    c[i] = -l[i];
            }
            else
            {
                if (s->d_set->values[i] < 0)
                    c[i] = -l[i];
                else
                    c[i] = s->punishment_factor - l[i];
            }

            c_sum += CLANN_FABS(c[i]);
        }

        if (CLANN_FABS(error) > c_sum)
        {
#if CLANN_DEBUG
            printf("W. [SVM] Solution %p filled with zeros.\n", l);
#endif
            for (i = 0; i < s->number_of_inputs; i++)
                l[i] = 0;
        }

        for (i = 0; i < s->number_of_inputs; i++)
            l[i] += (CLANN_FABS(error) * c[i]) / c_sum;
    }
}

clann_real_type
svm_compute_kernel(struct svm *s,
                   const clann_real_type *a,
                   const clann_real_type *b)
{
    clann_real_type v = 0;
    unsigned int i;

    switch(s->kernel_type)
    {
        case SVM_TYPE_RBF:

            for (i = 0; i < s->input_size; i++)
                v += CLANN_POW(a[i] - b[i], 2);

            return function_green_gaussian(s->rbf_width, v);

        case SVM_TYPE_MLP:

            for (i = 0; i < s->input_size; i++)
                v += a[i] * b[i];

            v = s->mlp_kappa * v + s->mlp_vartheta;

            return function_tanh(v);

        case SVM_TYPE_POLY:

            for (i = 0; i < s->input_size; i++)
                v += a[i] * b[i];

            v += 1;

            return CLANN_POW(v, s->poly_order);

        default:
            printf("E. [SVM] Invalid kernel type.\n");
            exit(EXIT_FAILURE);
    }

    return 0;
}
