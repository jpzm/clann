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

#ifndef BIND_MATRIX_H
#define BIND_MATRIX_H

#include <Python.h>

#include "code/matrix.h"

static PyObject *MatrixError;

/**
 *
 */
static char size__doc__[] = "Return the size of matrix";

static PyObject*
size(PyObject *self, PyObject *args);

/**
 *
 */
static char new__doc__[] = "Create a new matrix";

static PyObject*
new(PyObject *self, PyObject *args);

/**
 *
 */
static char get__doc__[] = "Get a matrix value";

static PyObject*
get(PyObject *self, PyObject *args);

/**
 *
 */
static char set__doc__[] = "Set a matrix value";

static PyObject*
set(PyObject *self, PyObject *args);

/**
 *
 */
static char fill__doc__[] = "Fill a matrix with a value";

static PyObject*
fill(PyObject *self, PyObject *args);

/**
 *
 */
static char identity__doc__[] = "Create an identity matrix";

static PyObject*
identity(PyObject *self, PyObject *args);

/**
 *
 */
static char transpose__doc__[] = "Create a new transposed matrix";

static PyObject*
transpose(PyObject *self, PyObject *args);

/**
 *
 */
static char add__doc__[] = "Create a matrix from the sum of other two";

static PyObject*
add(PyObject *self, PyObject *args);

/**
 *
 */
static char subtract__doc__[] = "Create a matrix from the subtract of other \
two";

static PyObject*
subtract(PyObject *self, PyObject *args);

/**
 *
 */
static char product__doc__[] = "Create a matrix from the product of other two";

static PyObject*
product(PyObject *self, PyObject *args);

/**
 *
 */
static char inverse__doc__[] = "Create a inverse for a given matrix";

static PyObject*
inverse(PyObject *self, PyObject *args);

/**
 *
 */
static char pseudo_inverse__doc__[] = "Create a pseudo inverse for a given \
matrix";

static PyObject*
pseudo_inverse(PyObject *self, PyObject *args);

/**
 *
 */
static char isnull__doc__[] = "Check if a matrix is null";

static PyObject*
isnull(PyObject *self, PyObject *args);

/**
 *
 */
static PyMethodDef MatrixMethods[] =
{
    {"size", size, METH_VARARGS, size__doc__},
    {"new", new, METH_VARARGS, new__doc__},
    {"get", get, METH_VARARGS, get__doc__},
    {"set", set, METH_VARARGS, set__doc__},
    {"fill", fill, METH_VARARGS, fill__doc__},
    {"identity", identity, METH_VARARGS, identity__doc__},
    {"transpose", transpose, METH_VARARGS, transpose__doc__},
    {"add", add, METH_VARARGS, add__doc__},
    {"subtract", subtract, METH_VARARGS, subtract__doc__},
    {"product", product, METH_VARARGS, product__doc__},
    {"inverse", inverse, METH_VARARGS, inverse__doc__},
    {"pseudo_inverse", pseudo_inverse, METH_VARARGS, pseudo_inverse__doc__},
    {"isnull", isnull, METH_VARARGS, isnull__doc__},
    {NULL, NULL, 0, NULL}
};

/**
 *
 */
static char module__doc__[] = "CLANN matrix module";

PyMODINIT_FUNC
initmatrix(void);

#endif
