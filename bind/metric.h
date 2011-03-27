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

#ifndef BIND_METRIC_H
#define BIND_METRIC_H

#include <Python.h>

#include "code/metric.h"

static PyObject *MetricError;

/**
 *
 */
static char scale__doc__[] = "";

static PyObject*
scale(PyObject *self, PyObject *args);

/**
 *
 */
static char euclidean__doc__[] = "";

static PyObject*
euclidean(PyObject *self, PyObject *args);

/**
 *
 */
static char norm__doc__[] = "";

static PyObject*
norm(PyObject *self, PyObject *args);

/**
 *
 */
static char dot_product__doc__[] = "";

static PyObject*
dot_product(PyObject *self, PyObject *args);

/**
 *
 */
static char hausdorff__doc__[] = "";

static PyObject*
hausdorff(PyObject *self, PyObject *args);

/**
 *
 */
static char hausdorff_symmetric__doc__[] = "";

static PyObject*
hausdorff_symmetric(PyObject *self, PyObject *args);

/**
 *
 */
static char hausdorff_limit__doc__[] = "";

static PyObject*
hausdorff_limit(PyObject *self, PyObject *args);

/**
 *
 */
static char hausdorff_limit_symmetric__doc__[] = "";

static PyObject*
hausdorff_limit_symmetric(PyObject *self, PyObject *args);

/**
 *
 */
static char hausdorff_mean__doc__[] = "";

static PyObject*
hausdorff_mean(PyObject *self, PyObject *args);

/**
 *
 */
static char hausdorff_mean_symmetric__doc__[] = "";

static PyObject*
hausdorff_mean_symmetric(PyObject *self, PyObject *args);

/**
 *
 */
static char hausdorff_angle__doc__[] = "";

static PyObject*
hausdorff_angle(PyObject *self, PyObject *args);

/**
 *
 */
static char hausdorff_angle_symmetric__doc__[] = "";

static PyObject*
hausdorff_angle_symmetric(PyObject *self, PyObject *args);

/**
 *
 */
static PyMethodDef MatrixMethods[] =
{
    {"scale", scale, METH_VARARGS, scale__doc__},
    {"euclidean", euclidean, METH_VARARGS, euclidean__doc__},
    {"norm", norm, METH_VARARGS, norm__doc__},
    {"dot_product", dot_product, METH_VARARGS, dot_product__doc__},
    {"hausdorff", hausdorff, METH_VARARGS, hausdorff__doc__},
    {"hausdorff_symmetric",
        hausdorff_symmetric,
        METH_VARARGS,
        hausdorff_symmetric__doc__},
    {"hausdorff_limit",
        hausdorff_limit,
        METH_VARARGS,
        hausdorff_limit__doc__},
    {"hausdorff_limit_symmetric",
        hausdorff_limit_symmetric,
        METH_VARARGS,
        hausdorff_limit_symmetric__doc__},
    {"hausdorff_mean",
        hausdorff_mean,
        METH_VARARGS,
        hausdorff_mean__doc__},
    {"hausdorff_mean_symmetric",
        hausdorff_mean_symmetric,
        METH_VARARGS,
        hausdorff_mean_symmetric__doc__},
    {"hausdorff_angle",
        hausdorff_angle,
        METH_VARARGS,
        hausdorff_angle__doc__},
    {"hausdorff_angle_symmetric",
        hausdorff_angle_symmetric,
        METH_VARARGS,
        hausdorff_angle_symmetric__doc__},
    {NULL, NULL, 0, NULL}
};

/**
 *
 */
static char module__doc__[] = "CLANN metric module";

PyMODINIT_FUNC
initmetric(void);

#endif
