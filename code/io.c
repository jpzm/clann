/**
 * Copyright (C) 2008-2014 Joao Paulo de Souza Medeiros
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

#include "io.h"


clann_void_type
clann_io_extract_numbers(clann_matrix_type *m,
                         const clann_string_type line)
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


clann_bool_type
clann_io_read_double_data_file(const clann_string_type path,
                               clann_matrix_type *x,
                               clann_matrix_type *d)
{
    FILE *fd;

    clann_matrix_initialize(x, 0, 0);
    clann_matrix_initialize(d, 0, 0);

    if ((fd = fopen(path, "r")))
    {
        size_t length;
        int c = 1;
        char *line = NULL;

        while (true)
        {
            if (getline(&line, &length, fd) == -1)
                break;

            if (c == 1)
                clann_io_extract_numbers(x, line);
            else
                clann_io_extract_numbers(d, line);

            c *= -1;
        }

        return (c != 1) ? false : true;
    }

    return false;
}


clann_bool_type
clann_io_read_data_file(const clann_string_type path,
                        clann_matrix_type *v)
{
    FILE *fd;

    clann_matrix_initialize(v, 0, 0);

    if ((fd = fopen(path, "r")))
    {
        char *line = NULL;
        size_t len;

        while (getline(&line, &len, fd) != -1)
            clann_io_extract_numbers(v, line);

        return true;
    }

    return false;
}
