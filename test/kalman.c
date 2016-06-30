#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../code/io.h"
#include "../code/kalman.h"


int
main(int argc, char *argv[])
{
    int i;
    clann_kalman_type k;
    clann_matrix_type m;

    clann_io_read_data_file(argv[1], &m);

    clann_kalman_initialize(&k, 4, 1, 0);

    /*
     * Filter initial state estimation
     */
    clann_real_type state[] = {0, 0, 0, 0};
    memcpy(k.state[KALMAN_A_POS].values, state, sizeof(state));

    /*
     * Filter state transition matrix
     */
    clann_real_type transition[] = { 1/4., 2/4.,    0,   0,
                                     3/4., 1/4., 1/4.,   0,
                                        0, 1/4., 1/4., 3/4.,
                                        0,    0, 2/4., 1/4. };
    memcpy(k.m_process.values, transition, sizeof(transition));
    //clann_matrix_print(&k.m_process);

    *clann_matrix_value(&k.m_measure, 0, 0) = 1;
    *clann_matrix_value(&k.m_measure, 0, 1) = 0;
    *clann_matrix_value(&k.m_measure, 0, 2) = 0;
    *clann_matrix_value(&k.m_measure, 0, 3) = 0;
    //clann_matrix_print(&k.m_measure);
    clann_matrix_scale(&k.process_noise_cov, 1e-5);
    clann_matrix_scale(&k.measure_noise_cov, 1e-3);
    //clann_matrix_print(&k.process_noise_cov);
    //clann_matrix_print(&k.measure_noise_cov);
    //clann_matrix_print(&k.m_predict[KALMAN_A_POS]);

    for (i = 0; i < m.rows; i++)
    {
        clann_kalman_predict(&k);
        *clann_matrix_value(&k.measure, 0, 0) = *clann_matrix_value(&m, i, 1);

        //clann_matrix_print(&k.state[KALMAN_A_PRI]);
        clann_kalman_correct(&k);
        //clann_matrix_print(&k.state[KALMAN_A_POS]);
        state[0] = *clann_matrix_value(&m, i, 1);
        state[1] = *clann_matrix_value(&k.state[KALMAN_A_POS], 1, 0);
        state[2] = *clann_matrix_value(&k.state[KALMAN_A_POS], 2, 0);
        state[3] = *clann_matrix_value(&k.state[KALMAN_A_POS], 3, 0);

        printf("%d %Lf %Lf %Lf %Lf\n", i,
                state[0], state[1], state[2], state[3]);
    }

    clann_kalman_finalize(&k);
    clann_matrix_finalize(&m);

    return 0;
}

