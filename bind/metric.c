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

#include "bind/metric.h"

PyObject*
scale(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    clann_real_type v, f[2], t[2];

    if (!PyArg_ParseTuple(args, "d(dd)(dd)", &v, &f[0], &f[1], &t[0], &t[1]))
        return NULL;

    /**
     * Call the function
     */
    v = metric_scale(v, f, t);

    /**
     * Convert output
     */
    return Py_BuildValue("d", (double) v);
}

PyObject*
euclidean(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    PyObject *a = NULL,
             *b = NULL;

    if (!PyArg_ParseTuple(args, "OO", &a, &b))
        return NULL;

    /**
     * Call the function
     */
    struct matrix *x = PyCObject_AsVoidPtr(a),
                  *y = PyCObject_AsVoidPtr(b);

    if (x->cols != y->cols)
    {
        PyErr_SetString(PyExc_RuntimeError,
                        "matrices does not have the same size");
        return NULL;
    }

    clann_real_type v = metric_euclidean(x->values, y->values, x->cols);

    /**
     * Convert output
     */
    return Py_BuildValue("d", (double) v);
}

PyObject*
norm(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    PyObject *a = NULL;

    if (!PyArg_ParseTuple(args, "O", &a))
        return NULL;

    /**
     * Call the function
     */
    struct matrix *x = PyCObject_AsVoidPtr(a);

    clann_real_type v = metric_norm(x->values, x->cols);

    /**
     * Convert output
     */
    return Py_BuildValue("d", (double) v);
}

PyObject*
dot_product(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    PyObject *a = NULL,
             *b = NULL;

    if (!PyArg_ParseTuple(args, "OO", &a, &b))
        return NULL;

    /**
     * Call the function
     */
    struct matrix *x = PyCObject_AsVoidPtr(a),
                  *y = PyCObject_AsVoidPtr(b);

    if (x->cols != y->cols)
    {
        PyErr_SetString(PyExc_RuntimeError,
                        "matrices does not have the same size");
        return NULL;
    }

    clann_real_type v = metric_dot_product(x->values, y->values, x->cols);

    /**
     * Convert output
     */
    return Py_BuildValue("d", (double) v);
}

PyObject*
hausdorff(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    PyObject *a = NULL,
             *b = NULL;

    if (!PyArg_ParseTuple(args, "OO", &a, &b))
        return NULL;

    /**
     * Call the function
     */
    struct matrix *x = PyCObject_AsVoidPtr(a),
                  *y = PyCObject_AsVoidPtr(b);

    clann_real_type v = metric_hausdorff(x, y);

    /**
     * Convert output
     */
    return Py_BuildValue("d", (double) v);
}

PyObject*
hausdorff_symmetric(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    PyObject *a = NULL,
             *b = NULL;

    if (!PyArg_ParseTuple(args, "OO", &a, &b))
        return NULL;

    /**
     * Call the function
     */
    struct matrix *x = PyCObject_AsVoidPtr(a),
                  *y = PyCObject_AsVoidPtr(b);

    clann_real_type v = metric_hausdorff_symmetric(x, y);

    /**
     * Convert output
     */
    return Py_BuildValue("d", (double) v);
}

PyObject*
hausdorff_limit(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    PyObject *a = NULL,
             *b = NULL;
    clann_real_type limit;

    if (!PyArg_ParseTuple(args, "OOd", &a, &b, &limit))
        return NULL;

    /**
     * Call the function
     */
    struct matrix *x = PyCObject_AsVoidPtr(a),
                  *y = PyCObject_AsVoidPtr(b);

    clann_real_type v = metric_hausdorff_limit(x, y, limit);

    /**
     * Convert output
     */
    return Py_BuildValue("d", (double) v);
}

PyObject*
hausdorff_limit_symmetric(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    PyObject *a = NULL,
             *b = NULL;
    clann_real_type limit;

    if (!PyArg_ParseTuple(args, "OOd", &a, &b, &limit))
        return NULL;

    /**
     * Call the function
     */
    struct matrix *x = PyCObject_AsVoidPtr(a),
                  *y = PyCObject_AsVoidPtr(b);

    clann_real_type v = metric_hausdorff_limit_symmetric(x, y, limit);

    /**
     * Convert output
     */
    return Py_BuildValue("d", (double) v);
}

PyObject*
hausdorff_mean(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    PyObject *a = NULL,
             *b = NULL;

    if (!PyArg_ParseTuple(args, "OO", &a, &b))
        return NULL;

    /**
     * Call the function
     */
    struct matrix *x = PyCObject_AsVoidPtr(a),
                  *y = PyCObject_AsVoidPtr(b);

    clann_real_type v = metric_hausdorff_mean(x, y);

    /**
     * Convert output
     */
    return Py_BuildValue("d", (double) v);
}

PyObject*
hausdorff_mean_symmetric(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    PyObject *a = NULL,
             *b = NULL;

    if (!PyArg_ParseTuple(args, "OO", &a, &b))
        return NULL;

    /**
     * Call the function
     */
    struct matrix *x = PyCObject_AsVoidPtr(a),
                  *y = PyCObject_AsVoidPtr(b);

    clann_real_type v = metric_hausdorff_mean_symmetric(x, y);

    /**
     * Convert output
     */
    return Py_BuildValue("d", (double) v);
}

PyObject*
hausdorff_angle(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    PyObject *a = NULL,
             *b = NULL;
    clann_real_type limit;

    if (!PyArg_ParseTuple(args, "OOd", &a, &b, &limit))
        return NULL;

    /**
     * Call the function
     */
    struct matrix *x = PyCObject_AsVoidPtr(a),
                  *y = PyCObject_AsVoidPtr(b);

    clann_real_type v = metric_hausdorff_angle(x, y, limit);

    /**
     * Convert output
     */
    return Py_BuildValue("d", (double) v);
}

PyObject*
hausdorff_angle_symmetric(PyObject *self, PyObject *args)
{
    /**
     * Convert input
     */
    PyObject *a = NULL,
             *b = NULL;
    clann_real_type limit;

    if (!PyArg_ParseTuple(args, "OOd", &a, &b, &limit))
        return NULL;

    /**
     * Call the function
     */
    struct matrix *x = PyCObject_AsVoidPtr(a),
                  *y = PyCObject_AsVoidPtr(b);

    clann_real_type v = metric_hausdorff_angle_symmetric(x, y, limit);

    /**
     * Convert output
     */
    return Py_BuildValue("d", (double) v);
}

PyMODINIT_FUNC
initmetric(void)
{
    PyObject *m;

    m = Py_InitModule4("metric",
            MatrixMethods,
            module__doc__,
            (PyObject *)NULL,
            PYTHON_API_VERSION);

    if (m == NULL)
        return;

    MetricError = PyErr_NewException("metric.error", NULL, NULL);
    Py_INCREF(MetricError);
    PyModule_AddObject(m, "error", MetricError);

    if (PyErr_Occurred())
        Py_FatalError("can't initialize module metric");
}
