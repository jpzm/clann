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

#include "fft.h"

void fft(complex **x,
         unsigned int *n,
         const unsigned char mode)
{
    unsigned int l = clann_nextpow2(*n);

    if (l > *n)
    {
#if CLANN_VERBOSE
        printf("N. [FFT] padding input with zeros from %d to %d.\n", *n, l);
#endif
        *x = realloc(*x, sizeof(complex) * l);

        unsigned int i;
        for (i = 0; i < l - *n; i++)
            (*x)[*n + i] = 0;

        *n = l;
    }

    fft_reverse(*x, l);
    fft_perform(*x, l, mode);
}

void fft_reverse(complex *x, const unsigned int n)
{
    unsigned int m, i, j = 0;
    for (i = 0; i < n; ++i)
    {
        if (j > i)
            CLANN_SWAP(x[i], x[j]);

        m = n;

        while (j & (m >>= 1))
            j &= ~m;

        j |= m;
    }
}

void fft_perform(complex *x, const unsigned int n, const unsigned char mode)
{
    unsigned int s, j, g, p, m;
    complex am, ap, f;
    double d,
           as,
           pi = mode ? M_PI : -M_PI;

    for (s = 1; s < n; s <<= 1)
    {
        j = s << 1;
        d = pi / (double) s;
        as = sin(d * 0.5);
        am = -2.0 * as * as + sin(d) * I;
        f = 1.0;

        for (g = 0; g < s; ++g)
        {
            for (p = g; p < n; p += j)
            {
                m = p + s;
                ap = f * x[m];
                x[m] = x[p] - ap;
                x[p] = x[p] + ap;
            }

            f = f + am * f;
        }
    }
}
