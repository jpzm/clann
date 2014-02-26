/**
 * Copyright (C) 2009-2014 Joao Paulo de Souza Medeiros
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

#ifndef PERIODOGRAM_H
#define PERIODOGRAM_H

#include <stdlib.h>
#include <complex.h>
#include "clann.h"
#include "fft.h"


/**
 *
 */
struct periodogram
{
    clann_real_type *i;
    unsigned int q;
    unsigned int l;
    unsigned int k;
    unsigned int r;
};


/**
 * Initialize an given periodogram
 */
void
periodogram_initialize(struct periodogram *p,
                       unsigned int q,
                       unsigned int l,
                       unsigned int k);

/**
 * Finalize an given periodogram
 */
void
periodogram_finalize(struct periodogram *a);

/**
 * Periodogram averaging function
 */
void
periodogram(struct periodogram *p,
            complex const *x,
            unsigned int n);

#endif
