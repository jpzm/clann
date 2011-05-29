/**
 * Copyright (C) 2010 Joao Paulo de Souza Medeiros
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

#include "graph.h"


inline clann_bool_type
graph_default_f_node_eq(void *a, void *b)
{
    return a == b;
}

void
graph_initialize(struct graph *g)
{
    g->n_node = 0;
    g->n_edge = 0;
    g->l_node = NULL;
    g->l_edge = NULL;
    g->directed = false;
    g->f_node_eq = &graph_default_f_node_eq;
}

void
graph_finalize(struct graph *g)
{
    clann_list_finalize(graph_get_edge_list(g));
    clann_list_finalize(graph_get_node_list(g));
    graph_destroy_adjacency_list(g);
    free((void *) g);
}

int
graph_copy(const struct graph *ga,
           struct graph *gb)
{
    // TODO: what? everything!
    return 0;
}

void
graph_destroy_adjacency_list(struct graph *g)
{
    unsigned int i;

    if (g->l_near != NULL)
    {
        for (i = 0; i < g->n_node; i++)
            clann_list_finalize(g->l_near[i]);

        free(g->l_near);
    }
}

void
graph_create_adjacency_list(struct graph *g)
{
    unsigned int i;

    /**
     * Clear list if it already exists
     */
    graph_destroy_adjacency_list(g);

    /**
     * Create a new adjacency list
     */
    struct adjacency *a;

    g->l_near = malloc(g->n_node * sizeof(clann_list_type *));

    // Initializing lists
    for (i = 0; i < g->n_edge; i++)
        g->l_near[i] = NULL;

    for (i = 0; i < g->n_edge; i++)
    {
        a = malloc(sizeof(struct adjacency));
        a->e = (struct edge *) g->l_edge[i].info;
        a->n = a->e->nb;
        clann_list_insert(&g->l_near[a->e->na->id], (void *) a);

        if (!g->directed)
        {
            a = malloc(sizeof(struct adjacency));
            a->e = (struct edge *) g->l_edge[i].info;
            a->n = a->e->na;
            clann_list_insert(&g->l_near[a->e->nb->id], (void *) a);
        }
    }
}

struct edge *
graph_get_edge(struct graph *g,
               clann_id_type id)
{
    clann_list_type *l = graph_get_edge_list(g);
    struct edge *e;

    while (l)
    {
        e = (struct edge *) l->info;

        if (e->id == id)
            return e;

        l = l->next;
    }

    return NULL;
}

struct edge *
graph_get_edge_by_nodes(struct graph *g,
                        struct node *na,
                        struct node *nb)
{
    clann_list_type *l = graph_get_edge_list(g);
    struct edge *e;

    while (l)
    {
        e = (struct edge *) l->info;

        if ((e->na == na && e->nb == nb) ||
            (!g->directed && e->na == nb && e->nb == na))
            return e;

        l = l->next;
    }

    return NULL;
}

struct node *
graph_get_node(struct graph *g,
               clann_id_type id)
{
    clann_list_type *l = graph_get_node_list(g);
    struct node *n;

    while (l)
    {
        n = (struct node *) l->info;

        if (n->id == id)
            return n;

        l = l->next;
    }

    return NULL;
}

struct node *
graph_get_node_by_info(struct graph *g,
                       void *info)
{
    clann_list_type *l = graph_get_node_list(g);
    struct node *n;

    while (l)
    {
        n = (struct node *) l->info;

        if (g->f_node_eq(n->info, info))
            return n;

        l = l->next;
    }

    return NULL;
}

struct edge *
graph_add_edge(struct graph *g,
               struct node *na,
               struct node *nb,
               void *info)
{
    struct edge *e = malloc(sizeof(struct edge));

    e->id = g->n_edge++;
    e->na = na;
    e->nb = nb;
    e->info = info;
    e->attr = NULL;
    e->status = on;

    clann_list_insert(&g->l_edge, e);

    return e;
}

struct node *
graph_add_node(struct graph *g,
               void *info)
{
    struct node *n = malloc(sizeof(struct node));

    n->id = g->n_node++;
    n->info = info;
    n->attr = NULL;
    n->status = on;

    clann_list_insert(&g->l_node, n);

    return n;
}

clann_list_type *
graph_get_edges_by_node(struct graph *g,
                        struct node *n)
{
    clann_list_type *l = graph_get_edge_list(g);
    clann_list_type *r = NULL;
    struct edge *e;

    while (l)
    {
        e = (struct edge *) l->info;

        if (e->na == n || e->nb == n)
            clann_list_insert(&r, e);

        l = l->next;
    }

    return r;
}

clann_list_type *
graph_get_edge_list(struct graph *g)
{
    return g->l_edge;
}

clann_list_type *
graph_get_node_list(struct graph *g)
{
    return g->l_node;
}

clann_list_type *
graph_get_node_neighbors(struct graph *g,
                         struct node *n)
{
    clann_list_type *l = graph_get_edge_list(g);
    clann_list_type *r = NULL;
    struct edge *e;

    while (l)
    {
        e = (struct edge *) l->info;

        if (e->na == n)
            clann_list_insert(&r, e->nb);
        else if (e->nb == n)
            clann_list_insert(&r, e->na);

        l = l->next;
    }

    return r;
}

clann_real_type
graph_clustering(struct graph *g)
{
    clann_list_type *l = graph_get_node_list(g);
    clann_real_type size = g->n_node;
    struct node *n;

    g->clustering = 0;

    while (l)
    {
        n = (struct node *) l->info;
        g->clustering += graph_node_clustering(g, n);

        l = l->next;
    }

    g->clustering = g->clustering / size;

    return g->clustering;
}

clann_real_type
graph_node_clustering(struct graph *g,
                      struct node *n)
{
    clann_list_type *l, *i, *j, *neighbors = graph_get_node_neighbors(g, n);
    clann_real_type k, e = 0;
    clann_real_type r;
    struct node *x, *y;
    struct edge *o;

    k = clann_list_size(neighbors);
    j = neighbors;

    if (g->directed)
    {
        // TODO: compute clustering of direted graphs
        r = 0;
    }
    else
    {
        while (j)
        {
            x = (struct node *) j->info;
            i = neighbors;

            while (i)
            {
                y = (struct node *) i->info;
                l = graph_get_edge_list(g);

                while (l)
                {
                    o = (struct edge *) l->info;

                    if (
                        (o->na == x && o->nb == y) ||
                        (o->nb == x && o->na == y)
                       )
                        e++;

                    l = l->next;
                }

                i = i->next;
            }

            j = j->next;
        }

        r = (k * (k - 1));

        if (r > 0)
            r = 2 * e / r;
    }

    n->clustering = r;

    return n->clustering;
}

struct tree *
graph_spanning_tree(struct graph *g,
                    struct node *n)
{
    struct tree *t = malloc(sizeof(struct tree));
    struct tree_node *f, *p;
    struct node *m;
    clann_list_type *list, *e;
    clann_list_type *neighbor;

    tree_initialize(t);
    f = tree_add_node(t, NULL, (void *) n);
    clann_list_insert(&list, f);

    /**
     *
     */
    do
    {
        e = list;
        p = (struct tree_node *) e->info;
        neighbor = graph_get_node_neighbors(g, (struct node *) p->info);

        while (neighbor)
        {
            m = (struct node *) neighbor->info;
            f = tree_add_node(t, p, (void *) m);
            clann_list_insert(&list, f);

            neighbor = neighbor->next;
        }

        clann_list_remove(&list, e);
    }
    while (clann_list_size(list));

    return t;
}
