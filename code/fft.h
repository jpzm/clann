/**
 * Copyright (C) 2009 Joao Paulo de Souza Medeiros
 * Copyright (C) 2009 Adriano Monteiro Marques
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

#ifndef FFT_H
#define FFT_H

#include <stdlib.h>
#include <complex.h>
#include "clann.h"

#define FFT_FORWARD 0
#define FFT_INVERSE 1

/**
 * FFT function
 */
inline void
fft(complex **x,
    unsigned int *n,
    const unsigned char mode);

/**
 *
 */
inline void
fft_reverse(complex *x,
            const unsigned int n);

/**
 *
 */
inline void
fft_perform(complex *x,
            const unsigned int n,
            const unsigned char mode);

#endif
