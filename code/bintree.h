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

#ifndef BINTREE_H
#define BINTREE_H

#include <stdlib.h>
#include "clann.h"


/**
 *
 */
struct bintree_node
{
    clann_id_type id;
    struct bintree_node *parent;
    struct bintree_node *left;
    struct bintree_node *right;
    void *info; // used by external libraries and applications
    clann_key_type status;
};

/**
 * Tree structure
 */
struct bintree
{
    struct bintree_node *root;
    clann_size_type n_node;
    clann_size_type height;

    /**
     * This function tell if two nodes have the same information
     * (i.e. are equal).
     */
    clann_bool_type (*f_node_eq)(struct bintree_node *,
                                 struct bintree_node *);
};


/**
 * Initialize a given tree
 */
inline void
bintree_initialize(struct bintree *t);

/**
 * Finalize a given tree
 */
inline void
bintree_finalize(struct bintree *t);

/**
 * Creates a copy of a tree.
 */
int
bintree_copy(const struct bintree *ta,
             struct bintree *tb);

/**
 * Initialize a given tree node
 */
inline void
bintree_node_initialize(struct bintree_node *n);

/**
 * Finalize a given tree node
 */
inline void
bintree_node_finalize(struct bintree_node *n);

/**
 *
 */
struct bintree_node *
bintree_add_node(struct bintree *t,
                 struct bintree_node *n);

/**
 *
 */
struct bintree_node *
bintree_search_node_from(struct bintree *t,
                         struct bintree_node *r,
                         struct bintree_node *n);

/**
 *
 */
struct bintree_node *
bintree_search_node(struct bintree *t,
                    struct bintree_node *n);


#endif
