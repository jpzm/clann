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

#include "periodogram.h"


void periodogram_initialize(struct periodogram *p,
                            unsigned int q,
                            unsigned int l,
                            unsigned int k)
{
    p->q = q;
    p->l = l;
    p->k = k;
    p->r = (int) (p->q - p->l) / (p->k - 1);

    unsigned int i;
    if ((i = clann_nextpow2(p->q)) != p->q)
    {
#if CLANN_VERBOSE
        printf("N. [PERIODOGRAM] changing Q from %d to %d.\n", p->q, i);
#endif
        p->q = i;
    }

    p->i = malloc(sizeof(clann_real_type) * p->q);

    for (i = 0; i < p->q; i++)
        p->i[i] = 0;
}

void periodogram_finalize(struct periodogram *p)
{
    free(p->i);
}

void periodogram(struct periodogram *p,
                 complex const *s,
                 unsigned int n)
{
    complex xr[p->q], x[p->q];
    unsigned int i, k, l;

    /**
     * Filling x with signal data.
     */
    for (i = 0; i < p->q; i++)
    {
        if (i < n)
            x[i] = s[i];
        else
            x[i] = 0;
    }

    /**
     * For each segment
     */
    for (k = 0; k < p->k; k++)
    {
        for (l = 0; l < p->q; l++)
            if (l < p->l)
                xr[l] = x[k * p->r + l];
            else
                xr[l] = 0;

        fft_reverse(xr, p->q);
        fft_perform(xr, p->q, FFT_FORWARD);

        for (i = 0; i < p->q; i++)
            p->i[i] += creal(xr[i]) * creal(xr[i]);
    }

    for (i = 0; i < p->q; i++)
        p->i[i] /= p->l * p->k;
}
