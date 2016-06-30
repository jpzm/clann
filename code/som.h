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

#ifndef SOM_H
#define SOM_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "metric.h"
#include "io.h"
#include "clann.h"

#define SOM_FILE_HEADER "SOM"

#define SOM_GRID_1D 1
#define SOM_GRID_2D 2
#define SOM_GRID_3D 3

typedef enum
{
    SOM_GRID_LINE,
    SOM_GRID_SQUARE,
    SOM_GRID_CUBE
} som_grid_type;


/**
 * Self-Organized Map structure
 */
struct som_grid
{
    som_grid_type type;
    clann_size_type width;
    clann_size_type dimension;
    clann_size_type n_neurons;
    clann_matrix_type indexes;
    clann_matrix_type weights;
};

struct som
{
    clann_size_type input_size;
    clann_real_type learning_rate;
    clann_real_type const_1;
    clann_real_type const_2;
    struct som_grid grid;
    unsigned int step;
    volatile unsigned int epoch;
    volatile clann_real_type actual_width;
    volatile clann_real_type actual_learning_rate;
};

/**
 *
 */
clann_void_type
som_initialize(struct som *ann,
               som_grid_type grid_type,
               clann_size_type input_size,
               clann_size_type width);

/**
 *
 */
clann_void_type
som_finalize(struct som *ann);

/**
 *
 */
clann_void_type
som_grid_indexes(struct som *ann,
                 clann_size_type index,
                 clann_real_type *buffer,
                 clann_size_type *count);

/**
 *
 */
clann_void_type
som_train_incremental(struct som *ann,
                      clann_matrix_type *x,
                      unsigned int epochs);

/**
 *
 */
clann_void_type
som_train_batch(struct som *ann,
                clann_matrix_type *x,
                unsigned int epochs);

/**
 *
 */
clann_void_type 
som_incremental_adjust_of_weights(struct som *ann,
                                  clann_real_type *x,
                                  clann_real_type *winner);

/**
 *
 */
clann_void_type 
som_batch_adjust_of_weights(struct som *ann,
                            clann_real_type *x,
                            clann_real_type *winner);

/**
 *
 */
clann_void_type
som_adjust_width(struct som *ann);

/**
 *
 */
clann_void_type
som_adjust_learning_rate(struct som *ann);

/**
 *
 */
clann_real_type*
som_grid_get_weights(struct som *ann,
                     unsigned int index);

/**
 *
 */
clann_void_type
som_find_winner_neuron(struct som *ann,
                       clann_real_type *x,
                       clann_real_type **winner);

/**
 *
 */
int
som_save(struct som *ann,
         const char *file);

/**
 *
 */
int
som_open(struct som *ann,
         const char *file);

#endif
