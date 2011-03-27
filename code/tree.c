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

#include "tree.h"


inline clann_bool_type
tree_default_f_node_eq(void *a, void *b)
{
    return a == b;
}

inline void
tree_initialize(struct tree *t)
{
    t->root = NULL;
    t->n_node = 0;
    t->f_node_eq = &tree_default_f_node_eq;
}

inline void
tree_finalize(struct tree *t)
{
    tree_node_finalize(t->root);
    free((void *) t);
}

int
tree_copy(const struct tree *ta,
          struct tree *tb)
{
    // TODO
    return 0;
}

inline void
tree_node_initialize(struct tree_node *n)
{
    n->id = -1;
    n->parent = NULL;
    n->l_child = NULL;
    n->info = NULL;
    n->attr = NULL;
    n->status = off;
}

inline void
tree_node_finalize(struct tree_node *n)
{
    clann_list_type *l = n->l_child;
    struct tree_node *c;

    while (l)
    {
        c = (struct tree_node *) n->info;
        tree_node_finalize(c);

        l = l->next;
    }

    free((void *) n);
}

struct tree_node *
tree_add_node(struct tree *t,
              struct tree_node *p,
              void *info)
{
    struct tree_node *n;

    if (p == NULL || tree_search_node(t, p->info))
    {
        n = malloc(sizeof(struct tree_node));

        tree_node_initialize(n);
        n->parent = p;
        n->info = info;
        n->status = on;

        t->n_node++;

        if (p == NULL)
            t->root = n;
        else 
            clann_list_insert(&p->l_child, n);

        return n;
    }

    return NULL;
}

struct tree_node *
tree_search_node_from(struct tree *t,
                      struct tree_node *r,
                      void *info)
{
    struct tree_node *n, *a;
    clann_list_type *l;

    /**
     * Checking for current node
     */
    if (t->f_node_eq(r->info, info))
        return r;

    /**
     * Recurssion/iteration over children
     */
    l = r->l_child;
    a = NULL;

    while (l && !a)
    {
        n = (struct tree_node *) l->info;
        a = tree_search_node_from(t, n, info);
        l = l->next;
    }

    return a;
}

struct tree_node *
tree_search_node(struct tree *t,
                 void *info)
{
    return tree_search_node_from(t, t->root, info);
}
