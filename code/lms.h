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

#ifndef LMS_H
#define LMS_H

#include <stdlib.h>
#include "clann.h"
#include "neuron.h"


/**
 * LMS structure
 */
struct lms
{
    clann_real_type learing_rate;
};


/**
 * Initialize LMS structure
 */
inline void
lms_initialize(struct lms *l,
               const clann_real_type learing_rate);

/**
 * LMS function
 */
inline void
lms_learn(struct neuron *n,
          struct lms *l,
          const clann_real_type *x,
          const clann_real_type d);

#endif
