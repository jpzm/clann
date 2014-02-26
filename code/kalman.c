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


void
kalman_initialize(struct kalman *k,
                  clann_size_type n_state,
                  clann_size_type n_measure,
                  clann_size_type n_control)
{
    k->n_state = n_state;
    k->n_measure = n_measure;
    k->n_control = n_control;

    matrix_initialize(&k->control, k->n_control, 1);
    matrix_initialize(&k->m_control, k->n_state, k->n_control);

    matrix_initialize(&k->state[KALMAN_A_PRI], k->n_state, 1);
    matrix_initialize(&k->state[KALMAN_A_POS], k->n_state, 1);
    matrix_initialize(&k->measure, k->n_measure, 1);

    matrix_initialize(&k->m_process, k->n_state, k->n_state);
    matrix_initialize(&k->m_measure, k->n_measure, k->n_state);
    matrix_initialize(&k->m_gain, k->n_state, k->n_measure);
    matrix_initialize(&k->m_predict[KALMAN_A_PRI], k->n_state, k->n_state);
    matrix_initialize(&k->m_predict[KALMAN_A_POS], k->n_state, k->n_state);

    matrix_initialize(&k->process_noise_cov, k->n_state, k->n_state);
    matrix_initialize(&k->measure_noise_cov, k->n_measure, k->n_measure);

    kalman_default(k);
}

void
kalman_finalize(struct kalman *k)
{
    /*
     * NOTE: maybe there is bug here.
     */
    matrix_finalize(&k->state[KALMAN_A_PRI]);
    matrix_finalize(&k->state[KALMAN_A_POS]);
    matrix_finalize(&k->measure);

    matrix_finalize(&k->control);
    matrix_finalize(&k->m_control);

    matrix_finalize(&k->m_process);
    matrix_finalize(&k->m_measure);
    matrix_finalize(&k->m_gain);
    matrix_finalize(&k->m_predict[KALMAN_A_PRI]);
    matrix_finalize(&k->m_predict[KALMAN_A_POS]);

    matrix_finalize(&k->process_noise_cov);
    matrix_finalize(&k->measure_noise_cov);
}

void
kalman_default(struct kalman *k)
{
    matrix_fill(&k->state[KALMAN_A_POS], 0);
    matrix_identity(&k->m_predict[KALMAN_A_POS], k->n_state);

    matrix_identity(&k->process_noise_cov, k->process_noise_cov.rows);
    matrix_identity(&k->measure_noise_cov, k->measure_noise_cov.rows);

    // should be defined by application
    if (k->n_control > 0)
    {
        matrix_fill(&k->control, 0);
        matrix_fill(&k->m_control, 0);
    }
    matrix_identity(&k->m_process, k->m_process.rows);
    matrix_fill(&k->m_measure, 0);
}

void
kalman_predict(struct kalman *k)
{
    struct matrix m;
    struct matrix t;

    matrix_initialize(&m, 0, 0);
    matrix_initialize(&t, 0, 0);

    /*
     * Predict the next state using the process equation:
     *   ~^x[k] = A ^x[k-1] + B u[k-1]
     */
    matrix_product(&k->m_process, &k->state[KALMAN_A_POS], &t);

    if (k->n_control > 0)
    {
        matrix_product(&k->m_control, &k->control, &m);
        matrix_add(&m, &t, &k->state[KALMAN_A_PRI]);
    }
    else
        matrix_copy(&t, &k->state[KALMAN_A_PRI]);

    /*
     * Predict the error covariance using equation:
     *   ~P[k] = A P[k-1] A' + Q
     */
    matrix_transpose(&k->m_process, &t);                 // t = A'
    matrix_product(&k->m_predict[KALMAN_A_POS], &t, &m); // m = P[k-1] A'
    matrix_product(&k->m_process, &m, &t);               // t = A P[k-1] A'
    matrix_add(&t, &k->process_noise_cov, &k->m_predict[KALMAN_A_PRI]);

    matrix_finalize(&m);
    matrix_finalize(&t);
}

void
kalman_correct(struct kalman *k)
{
    struct matrix m;
    struct matrix t;
    struct matrix s;

    matrix_initialize(&m, 0, 0);
    matrix_initialize(&t, 0, 0);
    matrix_initialize(&s, 0, 0);

    /*
     * Compute Kalman gain using equation:
     *   K[k] = ~P[k] C' inv(C ~P[k] C' + R)
     */
    matrix_transpose(&k->m_measure, &t);
    matrix_product(&k->m_predict[KALMAN_A_PRI], &t, &m); // m = ~P[k] C'
    matrix_product(&k->m_measure, &m, &t);               // t = C ~P[k] C'
    matrix_add(&t, &k->measure_noise_cov, &s);           // s = C ~P[k] C' + R
    matrix_inverse(&s, &t);
    matrix_product(&m, &t, &k->m_gain);

    /*
     * Update the estimate state using measurement:
     *   ^x[k] = ~^x[k] + K[k] (y[k] - C ~^x[k])
     */
    matrix_product(&k->m_measure, &k->state[KALMAN_A_PRI], &t);
    matrix_subtract(&k->measure, &t, &m);
    matrix_product(&k->m_gain, &m, &t);
    matrix_add(&k->state[KALMAN_A_PRI], &t, &k->state[KALMAN_A_POS]);

    /*
     * Update the error covariance:
     *   P[k] = (I - K[k] C) ~P[k]
     */
    matrix_product(&k->m_gain, &k->m_measure, &t);
    matrix_identity(&m, t.rows);
    matrix_subtract(&m, &t, &s);
    matrix_product(&s,
                   &k->m_predict[KALMAN_A_PRI],
                   &k->m_predict[KALMAN_A_POS]);

    matrix_finalize(&m);
    matrix_finalize(&t);
    matrix_finalize(&s);
}
