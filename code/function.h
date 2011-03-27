/**
 * Copyright (C) 2008 Joao Paulo de Souza Medeiros
 * Copyright (C) 2009 Adriano Monteiro Marques
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

#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdlib.h>
#include <math.h>
#include "clann.h"

#define FUNCTION_LINEAR             0
#define FUNCTION_STEP               1
#define FUNCTION_SIGNAL             2

#define FUNCTION_SIGMOID            3
#define FUNCTION_HYPERBOLIC_TANGENT 4

#define FUNCTION_GREEN_GAUSSIAN     5


/**
 * Activation step function
 */
inline clann_real_type
function_step(const clann_real_type *v);

/**
 * Activation signal function
 */
inline clann_real_type
function_signal(const clann_real_type *v);

/**
 * Activation sigmoid function
 */
inline clann_real_type
function_sigmoid(const clann_real_type *v);

/**
 * Activation hyperbolic tangent function
 */
inline clann_real_type
function_tanh(const clann_real_type *v);


/**
 * Green Gaussian function
 */
inline clann_real_type
function_green_gaussian(const clann_real_type *o,
                        const clann_real_type *v);

#endif
