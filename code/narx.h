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

#ifndef NARX_H
#define NARX_H

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "reader.h"
#include "clann.h"
#include "mlp.h"

/**
 * NARX network structure
 */
struct narx
{
    unsigned int delay;
    unsigned int recurrency;
    unsigned int input_size;
    clann_real_type *input;
    struct mlp ann;
};

/**
 *
 */
inline void
narx_initialize(struct narx *ann,
                unsigned int *architecture,
                const unsigned int number_of_layers,
                const unsigned int recurrency_size);

/**
 *
 */
inline void
narx_finalize(struct narx *ann);

/**
 *
 */
inline void
narx_insert_input(struct narx *ann,
                  const clann_real_type x);

/**
 *
 */
int
narx_save(struct narx *ann,
          const char *file);

/**
 *
 */
int
narx_open(struct narx *ann,
          const char *file);

#endif
