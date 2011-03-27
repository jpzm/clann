/**
 * Copyright (C) 2011 Joao Paulo de Souza Medeiros
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

#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include "clann.h"


/**
 *
 */
struct tree_node
{
    clann_id_type id;
    struct tree_node *parent;
    clann_list_type *l_child;
    void *info; // used by external libraries and applications
    void *attr; // used by external libraries and applications
    clann_key_type status;
};

/**
 * Tree structure
 */
struct tree
{
    struct tree_node *root;
    clann_size_type n_node;

    /**
     * This function tell if two nodes have the same information
     * (i.e. are equal).
     */
    clann_bool_type (*f_node_eq)(void *, void *);
};


/**
 * Initialize a given tree
 */
inline void
tree_initialize(struct tree *t);

/**
 * Finalize a given tree
 */
inline void
tree_finalize(struct tree *t);

/**
 * Creates a copy of a tree.
 */
int
tree_copy(const struct tree *ta,
          struct tree *tb);

/**
 * Initialize a given tree node
 */
inline void
tree_node_initialize(struct tree_node *n);

/**
 * Finalize a given tree node
 */
inline void
tree_node_finalize(struct tree_node *n);

/**
 *
 */
struct tree_node *
tree_add_node(struct tree *t,
              struct tree_node *p,
              void *info);

/**
 *
 */
struct tree_node *
tree_search_node_from(struct tree *t,
                      struct tree_node *r,
                      void *info);

/**
 *
 */
struct tree_node *
tree_search_node(struct tree *t,
                 void *info);


#endif
