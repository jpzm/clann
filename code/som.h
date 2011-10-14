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
#include "reader.h"
#include "clann.h"

#define SOM_GRID_RECTANGULAR    0
#define SOM_GRID_CIRCULAR       1
#define SOM_GRID_SPHERICAL      2

/**
 * Self-Organized Map structure
 */
struct som_grid
{
    unsigned int x_len;
    unsigned int y_len;
    struct matrix weights;
};

struct som
{
    unsigned int input_size;
    clann_real_type width;
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
inline void
som_initialize(struct som *ann,
               unsigned int input_size,
               unsigned int *dimension);

/**
 *
 */
inline void
som_finalize(struct som *ann);

/**
 *
 */
void
som_train_incremental(struct som *ann,
                      struct matrix *x,
                      unsigned int epochs);

/**
 *
 */
void
som_train_batch(struct som *ann,
                struct matrix *x,
                unsigned int epochs);

/**
 *
 */
inline void 
som_incremental_adjust_of_weights(struct som *ann,
                                  clann_real_type *x,
                                  clann_real_type *winner);

/**
 *
 */
inline void 
som_batch_adjust_of_weights(struct som *ann,
                            clann_real_type *x,
                            clann_real_type *winner);

/**
 *
 */
inline void
som_adjust_width(struct som *ann);

/**
 *
 */
inline void
som_adjust_learning_rate(struct som *ann);

/**
 *
 */
inline clann_real_type*
som_grid_get_weights(struct som_grid *grid,
                     unsigned int i,
                     unsigned int j);

/**
 *
 */
inline void
som_find_winner_neuron(struct som *ann,
                       clann_real_type *x,
                       clann_real_type *winner);

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
