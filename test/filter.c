/**
 * Copyright (C) 2008 Joao Paulo de Souza Medeiros.
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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "../code/lms.h"


#define USAGE "Usage: questao7 <learing_rate> <number_of_iterations>\n"


double sf(double n)
{
    return sin(0.075 * M_PI * n);
}

double vf()
{
    return 1 - drand48() * 2;
}

double v1f(double v1, double v)
{
    return -0.5 * v1 + v;
}

double v2f(double v2, double v)
{
    return 0.8 * v2 + v;
}


int main(int argc, char *argv[])
{
    double s, x, v, v1 = 0, v2 = 0, input[7];
    int iter, epochs, count = 7;
    struct neuron n;
    struct lms l;

    if (argc == 3)
    {
        initialize_neuron(&n, &count);
        initialize_lms(&l, atof(argv[1]));

        while (count--) input[count] = 0;

        epochs = atoi(argv[2]);
        count = 0;

        while (count < epochs)
        {
            s = sf((double) count++);
            v = vf();
            v1 = v1f(v1, v);
            v2 = v2f(v2, v);
            x = s + v1;

            iter = 5;
            while (iter--) input[iter + 1] = input[iter];

            input[6] = 1;
            input[0] = v2;

            lms_function(&n, &l, input, x);

            printf("%lf %lf %lf %lf\n", s, x, v, l.error);
        }

        free((void*) n.weights);
    }
    else
    {
        printf(USAGE);
        return 1;
    }

    return 0;
}
