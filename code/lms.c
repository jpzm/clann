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

#include "lms.h"


void
lms_initialize(struct lms *l,
               const clann_real_type learing_rate)
{
    l->learing_rate = learing_rate;
}

void
lms_learn(struct neuron *n,
          struct lms *l,
          const clann_real_type *x,
          const clann_real_type *d)
{
    neuron_compute_output(n, x);

    n->error = *d - n->output;
#if CLANN_VERBOSE
    printf("N. [LMS] Error: " CLANN_PRINTF ".\n", n->error);
#endif

    unsigned int i;
    for (i = 0; i < n->n_weights; i++)
        n->weights[i] += l->learing_rate * n->error * x[i];

    n->weights[i] += l->learing_rate * n->error * 1.0;
}
