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


#include "kalman.h"


clann_void_type
clann_kalman_initialize(clann_kalman_type *k,
                        clann_size_type n_state,
                        clann_size_type n_measure,
                        clann_size_type n_control)
{
    k->n_state = n_state;
    k->n_measure = n_measure;
    k->n_control = n_control;

    clann_matrix_initialize(&k->control, k->n_control, 1);
    clann_matrix_initialize(&k->m_control, k->n_state, k->n_control);

    clann_matrix_initialize(&k->state[KALMAN_A_PRI], k->n_state, 1);
    clann_matrix_initialize(&k->state[KALMAN_A_POS], k->n_state, 1);
    clann_matrix_initialize(&k->measure, k->n_measure, 1);

    clann_matrix_initialize(&k->m_process, k->n_state, k->n_state);
    clann_matrix_initialize(&k->m_measure, k->n_measure, k->n_state);
    clann_matrix_initialize(&k->m_gain, k->n_state, k->n_measure);
    clann_matrix_initialize(&k->m_predict[KALMAN_A_PRI],
                            k->n_state,
                            k->n_state);
    clann_matrix_initialize(&k->m_predict[KALMAN_A_POS],
                            k->n_state,
                            k->n_state);

    clann_matrix_initialize(&k->process_noise_cov, k->n_state, k->n_state);
    clann_matrix_initialize(&k->measure_noise_cov,
                            k->n_measure,
                            k->n_measure);

    clann_kalman_default(k);
}

clann_void_type
clann_kalman_finalize(clann_kalman_type *k)
{
    /*
     * NOTE: maybe there is bug here.
     */
    clann_matrix_finalize(&k->state[KALMAN_A_PRI]);
    clann_matrix_finalize(&k->state[KALMAN_A_POS]);
    clann_matrix_finalize(&k->measure);

    clann_matrix_finalize(&k->control);
    clann_matrix_finalize(&k->m_control);

    clann_matrix_finalize(&k->m_process);
    clann_matrix_finalize(&k->m_measure);
    clann_matrix_finalize(&k->m_gain);
    clann_matrix_finalize(&k->m_predict[KALMAN_A_PRI]);
    clann_matrix_finalize(&k->m_predict[KALMAN_A_POS]);

    clann_matrix_finalize(&k->process_noise_cov);
    clann_matrix_finalize(&k->measure_noise_cov);
}

clann_void_type
clann_kalman_default(clann_kalman_type *k)
{
    clann_matrix_fill(&k->state[KALMAN_A_POS], 0);
    clann_matrix_identity(&k->m_predict[KALMAN_A_POS], k->n_state);

    clann_matrix_identity(&k->process_noise_cov, k->process_noise_cov.rows);
    clann_matrix_identity(&k->measure_noise_cov, k->measure_noise_cov.rows);

    // should be defined by application
    if (k->n_control > 0)
    {
        clann_matrix_fill(&k->control, 0);
        clann_matrix_fill(&k->m_control, 0);
    }
    clann_matrix_identity(&k->m_process, k->m_process.rows);
    clann_matrix_fill(&k->m_measure, 0);
}

clann_void_type
clann_kalman_predict(clann_kalman_type *k)
{
    clann_matrix_type m;
    clann_matrix_type t;

    clann_matrix_initialize(&m, 0, 0);
    clann_matrix_initialize(&t, 0, 0);

    /*
     * Predict the next state using the process equation:
     *   ~^x[k] = A ^x[k-1] + B u[k-1]
     */
    clann_matrix_product(&k->m_process, &k->state[KALMAN_A_POS], &t);

    if (k->n_control > 0)
    {
        clann_matrix_product(&k->m_control, &k->control, &m);
        clann_matrix_add(&m, &t, &k->state[KALMAN_A_PRI]);
    }
    else
        clann_matrix_copy(&t, &k->state[KALMAN_A_PRI]);

    /*
     * Predict the error covariance using equation:
     *   ~P[k] = A P[k-1] A' + Q
     * using these steps:
     *   t = A'
     *   m = P[k-1] A'
     *   t = A P[k-1] A'
     */
    clann_matrix_transpose(&k->m_process, &t);
    clann_matrix_product(&k->m_predict[KALMAN_A_POS], &t, &m);
    clann_matrix_product(&k->m_process, &m, &t);
    clann_matrix_add(&t, &k->process_noise_cov, &k->m_predict[KALMAN_A_PRI]);

    clann_matrix_finalize(&m);
    clann_matrix_finalize(&t);
}

clann_void_type
clann_kalman_correct(clann_kalman_type *k)
{
    clann_matrix_type m;
    clann_matrix_type t;
    clann_matrix_type s;

    clann_matrix_initialize(&m, 0, 0);
    clann_matrix_initialize(&t, 0, 0);
    clann_matrix_initialize(&s, 0, 0);

    /*
     * Compute Kalman gain using equation:
     *   K[k] = ~P[k] C' inv(C ~P[k] C' + R)
     * using these steps:
     *   t = C'
     *   m = ~P[k] C'
     *   t = C ~P[k] C'
     *   s = C ~P[k] C' + R
     *   t = inv(C ~P[k] C' + R)
     */
    clann_matrix_transpose(&k->m_measure, &t);
    clann_matrix_product(&k->m_predict[KALMAN_A_PRI], &t, &m);
    clann_matrix_product(&k->m_measure, &m, &t);
    clann_matrix_add(&t, &k->measure_noise_cov, &s);
    clann_matrix_inverse(&s, &t);
    clann_matrix_product(&m, &t, &k->m_gain);

    /*
     * Update the estimate state using measurement:
     *   ^x[k] = ~^x[k] + K[k] (y[k] - C ~^x[k])
     */
    clann_matrix_product(&k->m_measure, &k->state[KALMAN_A_PRI], &t);
    clann_matrix_subtract(&k->measure, &t, &m);
    clann_matrix_product(&k->m_gain, &m, &t);
    clann_matrix_add(&k->state[KALMAN_A_PRI], &t, &k->state[KALMAN_A_POS]);

    /*
     * Update the error covariance:
     *   P[k] = (I - K[k] C) ~P[k]
     */
    clann_matrix_product(&k->m_gain, &k->m_measure, &t);
    clann_matrix_identity(&m, t.rows);
    clann_matrix_subtract(&m, &t, &s);
    clann_matrix_product(&s,
                         &k->m_predict[KALMAN_A_PRI],
                         &k->m_predict[KALMAN_A_POS]);

    clann_matrix_finalize(&m);
    clann_matrix_finalize(&t);
    clann_matrix_finalize(&s);
}
