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

#ifndef DPROG_H
#define DPROG_H

#include "fmdp.h"
#include "clann.h"


/**
 *
 */
void
dprog_policy_iteration(struct fmdp *mdp,
                       clann_real_type limit,
                       unsigned int max_epochs);

/**
 *
 */
void
dprog_value_iteration(struct fmdp *mdp,
                      clann_real_type limit,
                      unsigned int max_epochs);

/**
 *
 */
inline clann_real_type
dprog_state_value_function(struct fmdp *mdp,
                           unsigned int state);

/**
 *
 */
inline clann_real_type
dprog_action_value_function(struct fmdp *mdp,
                            unsigned int state,
                            unsigned int action);

/**
 *
 */
inline clann_real_type
dprog_deterministic_state_value_function(struct fmdp *mdp,
                                         unsigned int state,
                                         unsigned int action);

#endif
