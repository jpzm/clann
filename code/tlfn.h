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

#ifndef TLFN_H
#define TLFN_H

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "reader.h"
#include "clann.h"
#include "mlp.h"

/**
 * Time lagged feedforward network structure
 */
struct tlfn
{
    unsigned int input_size;
    clann_real_type *input;
    struct mlp ann;
};

/**
 *
 */
inline void
tlfn_initialize(struct tlfn *ann,
                unsigned int *architecture,
                const unsigned int number_of_layers);

/**
 *
 */
inline void
tlfn_finalize(struct tlfn *ann);

/**
 *
 */
inline void
tlfn_insert_input(struct tlfn *ann,
                  const clann_real_type x);

/**
 *
 */
int
tlfn_save(struct tlfn *ann,
          const char *file);

/**
 *
 */
int
tlfn_open(struct tlfn *ann,
          const char *file);

#endif
