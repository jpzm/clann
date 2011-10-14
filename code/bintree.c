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

#include "bintree.h"


inline clann_bool_type
bintree_default_f_node_eq(struct bintree_node *a,
                          struct bintree_node *b)
{
    return a->id == b->id;
}


inline void
tree_initialize(struct bintree *t)
{
    t->root = NULL;
    t->n_node = 0;
    t->height = 0;
    t->f_node_eq = &bintree_default_f_node_eq;
}

inline void
tree_finalize(struct bintree *t)
{
    bintree_node_finalize(t->root);
    free((void *) t);
}

int
tree_copy(const struct bintree *ta,
          struct bintree *tb)
{
    // TODO
    return 0;
}

inline void
tree_node_initialize(struct bintree_node *n)
{
    n->id = -1;
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    n->status = off;
}

inline void
tree_node_finalize(struct bintree_node *n)
{
    tree_node_finalize(n->left);
    tree_node_finalize(n->right);
    free((void *) n);
}

struct bintree_node *
bintree_add_node(struct bintree *t,
                 struct bintree_node *n)
{
    // TODO
    return NULL;
}

struct bintree_node *
bintree_search_node_from(struct bintree *t,
                         struct bintree_node *r,
                         struct bintree_node *n)
{
    struct bintree_node *p = r;

    if (t->f_node_eq(r, n))
        return r;

    if (n->id < r->id)
        return bintree_search_node_from(t, r->left, n);
    else if (n->id < r->id)
        return bintree_search_node_from(t, r->right, n);

    return NULL;
}

struct bintree_node *
bintree_search_node(struct bintree *t,
                    struct bintree_node *n)
{
    return bintree_search_node_from(t, t->root, n);
}

