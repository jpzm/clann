/**
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

#include "../code/svm.h"
#include "../code/matrix.h"
#include "../code/reader.h"

int main(int argc, char **argv)
{
    struct svm s;
    struct matrix x, d;

    clann_initialize();

    reader_read_double_data_file(argv[1], &x, &d);

    svm_initialize(&s, x.cols, x.rows);
    svm_compute_weights(&s, &x, &d);

    return 0;
}
