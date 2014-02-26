/**
 * Copyright (C) 2008-2014 Joao Paulo de Souza Medeiros
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

#include "dprog.h"


clann_real_type
dprog_state_value_function(struct fmdp *mdp,
                           unsigned int state)
{
    clann_real_type d, v = 0;
    unsigned int i;

    for (i = 0; i < mdp->number_of_actions; i++)
    {
        d = dprog_deterministic_state_value_function(mdp, state, i);
        v += *matrix_value(&mdp->policy, state, i) * d;
    }

    return v;
}

clann_real_type
dprog_deterministic_state_value_function(struct fmdp *mdp,
                                         unsigned int state,
                                         unsigned int action)
{
    clann_real_type p, r, sum = 0;
    unsigned int i;

    for (i = 0; i < mdp->number_of_states; i++)
    {
        p = mdp->f_probabilities(mdp,
                                 mdp->states[state],
                                 mdp->actions[action],
                                 mdp->states[i]);
        r = mdp->f_returns(mdp,
                           mdp->states[state],
                           mdp->actions[action],
                           mdp->states[i]);

        sum += p * (r + mdp->discount_rate * mdp->state_value.values[i]);
    }

    return sum;
}

void
dprog_policy_iteration(struct fmdp *mdp,
                       clann_real_type limit,
                       unsigned int max_epochs)
{
    clann_real_type q[mdp->number_of_actions],
               policy_change[mdp->number_of_actions];
    clann_real_type delta, v, max;
    unsigned int policy_stable = 0;
    unsigned int epoch = 0;
    unsigned int c, i, j;

    while ((max_epochs == 0 || epoch < max_epochs) && !policy_stable)
    {
        epoch += 1;

        /**
         * Policy evaluation
         */
        do
        {
            delta = 0;

            for (i = 0; i < mdp->number_of_states; i++)
            {
                v = mdp->state_value.values[i];
                mdp->state_value.values[i] = dprog_state_value_function(mdp,
                                                                        i);

                v = CLANN_FABS(v - mdp->state_value.values[i]);
                delta = (delta > v) ? delta : v;
            }
        }
        while (delta > limit);

        /**
         * Policy Improvement
         */
        policy_stable = 1;

        for (i = 0; i < mdp->number_of_states; i++)
        {
            max = -INT_MAX;
            c = 0;

            for (j = 0; j < mdp->number_of_actions; j++)
            {
                policy_change[j] = *matrix_value(&mdp->policy, i, j);
                q[j] = dprog_deterministic_state_value_function(mdp, i, j);

                if (q[j] >= max)
                {
                    max = q[j];
                    c = (q[j] == max ? c + 1 : 0);
                }
            }

            for (j = 0; j < mdp->number_of_actions; j++)
            {
                if (q[j] == max)
                    *matrix_value(&mdp->policy, i, j) = 1 / c;
                else
                    *matrix_value(&mdp->policy, i, j) = 0;

                if (policy_change[j] != *matrix_value(&mdp->policy, i, j))
                    policy_stable = 0;
            }
        }
    }
}

void
dprog_value_iteration(struct fmdp *mdp,
                      clann_real_type limit,
                      unsigned int max_epochs)
{
    //clann_real_type q[mdp->number_of_actions];
    clann_real_type delta, v/*, max*/;
    unsigned int policy_stable = 0;
    unsigned int epoch = 0;
    unsigned int /*c, */i/*, j*/;

    while ((max_epochs == 0 || epoch < max_epochs) && !policy_stable)
    {
        epoch += 1;

        /**
         * Policy evaluation
         */
        do
        {
            delta = 0;

            for (i = 0; i < mdp->number_of_states; i++)
            {
                v = mdp->state_value.values[i];
                mdp->state_value.values[i] = dprog_state_value_function(mdp,
                                                                        i);

                v = CLANN_FABS(v - mdp->state_value.values[i]);
                delta = (delta > v) ? delta : v;
            }
        }
        while (delta > limit);
    }
}
