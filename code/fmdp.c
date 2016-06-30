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

#include "fmdp.h"


clann_void_type
fmdp_initialize(struct fmdp *mdp,
                clann_real_type discount_rate,
                unsigned int number_of_states,
                unsigned int number_of_actions)
{
    mdp->discount_rate = discount_rate;
    mdp->number_of_states = number_of_states;
    mdp->number_of_actions = number_of_actions;

    clann_matrix_initialize(&mdp->policy,
                            mdp->number_of_states,
                            mdp->number_of_actions);
    clann_matrix_initialize(&mdp->state_value,
                            mdp->number_of_states,
                            1);
    clann_matrix_initialize(&mdp->action_value,
                            mdp->number_of_states,
                            mdp->number_of_actions);

    mdp->states = malloc(sizeof(clann_real_type) * mdp->number_of_states);
    mdp->actions = malloc(sizeof(clann_real_type) * mdp->number_of_actions);

    mdp->f_returns = NULL;
    mdp->f_probabilities = NULL;
}
