/**
 * Copyright (C) 2011-2014 Joao Paulo de Souza Medeiros
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

#ifndef CLANN_KALMAN_H
#define CLANN_KALMAN_H

#include <stdio.h>
#include <stdlib.h>
#include "clann.h"
#include "matrix.h"

#define KALMAN_A_PRI    0
#define KALMAN_A_POS    1


/**
 * Kalman filter basic structure
 */
typedef struct kalman
{
    clann_size_type n_state;
    clann_size_type n_measure;
    clann_size_type n_control;

    clann_matrix_type state[2];     // state, x
    clann_matrix_type measure;      // measure, y
    clann_matrix_type control;      // control (input), u

    clann_matrix_type m_process;    // state transition matrix, A
    clann_matrix_type m_control;    // control (input) matrix, B
    clann_matrix_type m_measure;    // measurement matrix, C
    clann_matrix_type m_gain;       // kalman gain matrix, K
    clann_matrix_type m_predict[2]; // prediction error covariance matrix, P

    clann_matrix_type process_noise_cov;    // process noise covariance, Q
    clann_matrix_type measure_noise_cov;    // measurement noise covariance, R
} clann_kalman_type;


/**
 * Initialize an given kalman structure description
 */
clann_void_type
clann_kalman_initialize(clann_kalman_type *k,
                        clann_size_type n_state,
                        clann_size_type n_measure,
                        clann_size_type n_control);

/**
 * Finalize an given kalman structure description
 */
clann_void_type
clann_kalman_finalize(clann_kalman_type *k);

/**
 * 
 */
clann_void_type
clann_kalman_default(clann_kalman_type *k);

/**
 * 
 */
clann_void_type
clann_kalman_predict(clann_kalman_type *k);

/**
 * 
 */
clann_void_type
clann_kalman_correct(clann_kalman_type *k);

#endif
