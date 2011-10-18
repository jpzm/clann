/**
 * Copyright (C) 2008 Joao Paulo de Souza Medeiros
 * Copyright (C) 2009 Adriano Monteiro Marques
 * Copyright (C) 2010 Joao Paulo de Souza Medeiros
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

#include "reader.h"


void
reader_extract_numbers(struct matrix *m,
                       const char *line)
{
    clann_size_type total = 0,
                    index = 0,
                    count = 0,
                    point = 0,
                    sline = (clann_size_type) strlen(line);
    clann_real_type number,
                    max = 0,
                    min = 0;

    while (sline > point)
    {
        while (*(line + point) == ' ')
            point++;

        index = m->rows * m->cols;
        total = sizeof(clann_real_type) * (index + count + 1);

        m->values = realloc(m->values, total);

        sscanf((line + point), CLANN_SCANF, &number);
        m->values[index + count] = number;

        if (count == 0)
        {
            max = number;
            min = number;
        }

        if (number > max)
            max = number;

        if (number < min)
            min = number;

        while (*(line + point) != ' ' && sline > point)
            point++;

        count++;
    }

    /*
     * Refresh the max and min numbers in the matrix structure.
     */
    if (m->cols == 0)
    {
        m->cols = count;
        m->max = max;
        m->min = min;
    }

    if (max > m->max)
        m->max = max;

    if (min < m->min)
        m->min = min;

    m->rows++;
}


int
reader_read_double_data_file(const char *path,
                             struct matrix *x,
                             struct matrix *d)
{
    FILE *fd;

    matrix_initialize(x, 0, 0);
    matrix_initialize(d, 0, 0);

    if ((fd = fopen(path, "r")))
    {
        unsigned int length;
        int c = 1;
        char *line = NULL;

        while (1)
        {
            if (getline(&line, &length, fd) == -1)
                break;

            if (c == 1)
                reader_extract_numbers(x, line);
            else
                reader_extract_numbers(d, line);

            c *= -1;
        }

        return (c != 1) ? 0 : 1;
    }

    return 0;
}


int
reader_read_data_file(const char *path,
                      struct matrix *v)
{
    FILE *fd;

    matrix_initialize(v, 0, 0);

    if ((fd = fopen(path, "r")))
    {
        char *line = NULL;
        unsigned int len;

        while (getline(&line, &len, fd) != -1)
            reader_extract_numbers(v, line);

        return 1;
    }

    return 0;
}
