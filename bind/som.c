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

#include "bind/som.h"

void
delete_matrix(struct matrix *a)
{
    matrix_finalize(a);
    free((void *) a);
}

void
delete_som(struct som *s)
{
    som_finalize(s);
    free((void *) s);
}

PyObject*
size(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    PyObject *m = NULL;

    if (!PyArg_ParseTuple(args, "O", &m))
        return NULL;

    /**
     * Call the function
     */
    struct som *a = (struct som *) PyCObject_AsVoidPtr(m);

    /**
     * Convert output
     */
    return Py_BuildValue("II", a->grid.x_len, a->grid.y_len);
}

PyObject*
new(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    unsigned int i, d[2];

    if (!PyArg_ParseTuple(args, "I(II)", &i, &d[0], &d[1]))
        return NULL;

    /**
     * Call the function
     */
    struct som *a = (struct som *) malloc(sizeof(struct som));

    som_initialize(a, i, d);

    /**
     * Convert output
     */
    return PyCObject_FromVoidPtr(a, (void *) delete_som);
}

PyObject*
get(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    unsigned int row, col;
    PyObject *m = NULL;

    if (!PyArg_ParseTuple(args, "OII", &m, &row, &col))
        return NULL;

    /**
     * Call the function
     */
    struct matrix *n = (struct matrix *) malloc(sizeof(struct matrix));
    struct som *a = (struct som *) PyCObject_AsVoidPtr(m);

    if (row >= a->grid.y_len || col >= a->grid.x_len)
    {
        PyErr_SetString(PyExc_IndexError, "indexes exceed output size");
        return NULL;
    }

    n->rows = 1;
    n->cols = a->grid.x_len;
    n->values = som_grid_get_weights(&a->grid, row, col);

    /**
     * Convert output
     */
    return PyCObject_FromVoidPtr(n, (void *) delete_matrix);
}

PyObject*
train(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    PyObject *s = NULL,
             *m = NULL;
    unsigned int i;

    if (!PyArg_ParseTuple(args, "OOI", &s, &m, &i))
        return NULL;

    /**
     * Call the function
     */
    struct matrix *n = (struct matrix *) PyCObject_AsVoidPtr(m);
    struct som *a = (struct som *) PyCObject_AsVoidPtr(s);

    if (i < 1)
    {
        PyErr_SetString(PyExc_IndexError,
                "number of iterations must be positive");
        return NULL;
    }

    som_training(a, n, i);

    /**
     * Convert output
     */
    Py_INCREF(Py_None);
    return Py_None;
}

PyMODINIT_FUNC
initsom(void)
{
    PyObject *m;

    m = Py_InitModule4("som",
            SOMMethods,
            module__doc__,
            (PyObject *)NULL,
            PYTHON_API_VERSION);

    if (m == NULL)
        return;

    SOMError = PyErr_NewException("som.error", NULL, NULL);
    Py_INCREF(SOMError);
    PyModule_AddObject(m, "error", SOMError);

    if (PyErr_Occurred())
        Py_FatalError("can't initialize module som");
}
