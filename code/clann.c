/**
 * Copyright (C) 2008 Joao Paulo de Souza Medeiros
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

#include "clann.h"


void
clann_initialize()
{
    FILE *fp = fopen("/dev/urandom", "r");
    unsigned int foo;
    struct timeval t;

    if(!fp)
    {
        gettimeofday(&t, NULL);
        foo = t.tv_usec;
#if CLANN_DEBUG
        printf("W. [CLANN] Unable to open /dev/urandom.\n");
#endif
    }
    else
    {
        fread(&foo, sizeof(foo), 1, fp);
        fclose(fp);
    }

    srand(foo);
}

void
clann_shuffle(clann_int_type *list,
              clann_size_type length)
{
    unsigned int i, ri, a;
    for (i = 0; i < length; i++)
    {
        ri = (unsigned int) clann_rand(0 , length - 1);

        a = list[i];
        list[i] = list[ri];
        list[ri] = a;
    }
}

clann_real_type
clann_nrand()
{
    return rand() / (RAND_MAX + 1.0);
}

clann_real_type
clann_rand(const clann_real_type min,
           const clann_real_type max)
{
    return (max - min) * clann_nrand() + min;
}

clann_int_type
clann_randint(const clann_int_type min,
              const clann_int_type max)
{
    return (clann_int_type) rint((max - min) * clann_nrand() + min);
}

clann_real_type
clann_factorial(const clann_uint_type v)
{
    clann_real_type a = 1;
    unsigned int i;

    for (i = 0; i < v; i++)
        a *= v - i;

    return a;
}

clann_real_type
clann_binomial(const clann_uint_type n,
               const clann_uint_type k)
{
    unsigned int i;

    if (k < 0 || k > n)
        return 0;

    clann_real_type a = 1, b = 1;

    for (i = 0; i < k; i++)
    {
        a *= n - i;
        b *= k - i;
    }

    return a / b;
}

clann_uint_type
clann_nextpow2(clann_uint_type n)
{
    unsigned int i = 2;

    if (n == 0)
        return 1;

    while (i < n)
        i *= 2;

    return i;
}
