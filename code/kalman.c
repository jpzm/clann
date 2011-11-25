/**
 * Copyright (C) 2011 Joao Paulo de Souza Medeiros
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

    matrix_initialize(&k->state[KALMAN_A_PRI], k->n_state, 1);
    matrix_initialize(&k->state[KALMAN_A_POS], k->n_state, 1);
    matrix_initialize(&k->measure, k->n_measure, 1);
    matrix_initialize(&k->control, k->n_control, 1);

    matrix_initialize(&k->m_process, k->n_state, k->n_state);
    matrix_initialize(&k->m_measure, k->n_measure, k->n_state);
    matrix_initialize(&k->m_control, k->n_state, k->n_control);
    matrix_initialize(&k->m_gain, k->n_state, k->n_measure);
    matrix_initialize(&k->m_predict[KALMAN_A_PRI], k->n_state, k->n_state);
    matrix_initialize(&k->m_predict[KALMAN_A_POS], k->n_state, k->n_state);

    matrix_initialize(&k->process_noise_cov, k->n_state, k->n_state);
    matrix_initialize(&k->measure_noise_cov, k->n_measure, k->n_measure);
}

void
kalman_finalize(struct kalman *k)
{
    matrix_finalize(&k->state[KALMAN_A_PRI]);
    matrix_finalize(&k->state[KALMAN_A_POS]);
    matrix_finalize(&k->measure);
    matrix_finalize(&k->control);

    matrix_finalize(&k->m_process);
    matrix_finalize(&k->m_measure);
    matrix_finalize(&k->m_control);
    matrix_finalize(&k->m_gain);
    matrix_finalize(&k->m_predict[KALMAN_A_PRI]);
    matrix_finalize(&k->m_predict[KALMAN_A_POS]);

    matrix_finalize(&k->process_noise_cov);
    matrix_finalize(&k->measure_noise_cov);
}

void
kalman_predict(struct kalman *k,
               const clann_real_type *c)
{
    // TODO
}

void
kalman_correct(struct kalman *k,
               const clann_real_type *m)
{
    // TODO
}
