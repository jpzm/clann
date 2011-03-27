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

#ifndef BIND_SOM_H
#define BIND_SOM_H

#include <Python.h>

#include "code/som.h"

static PyObject *SOMError;

/**
 *
 */
static char size__doc__[] = "Return the size of SOM output layer";

static PyObject*
size(PyObject *self, PyObject *args);

/**
 *
 */
static char new__doc__[] = "Create a new SOM";

static PyObject*
new(PyObject *self, PyObject *args);

/**
 *
 */
static char get__doc__[] = "Get neuron values";

static PyObject*
get(PyObject *self, PyObject *args);

/**
 *
 */
static char train__doc__[] = "Start training SOM";

static PyObject*
train(PyObject *self, PyObject *args);

/**
 *
 */
static PyMethodDef SOMMethods[] =
{
    {"size", size, METH_VARARGS, size__doc__},
    {"new", new, METH_VARARGS, new__doc__},
    {"get", get, METH_VARARGS, get__doc__},
    {"train", train, METH_VARARGS, train__doc__},
    {NULL, NULL, 0, NULL}
};

/**
 *
 */
static char module__doc__[] = "CLANN self-organizing map (SOM) module";

PyMODINIT_FUNC
initsom(void);

#endif
