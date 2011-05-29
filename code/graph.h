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

#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include "tree.h"
#include "clann.h"


/**
 *
 */
struct edge
{
    clann_id_type id;
    struct node *na;
    struct node *nb;
    void *info; // used by external libraries and applications
    void *attr; // used by external libraries and applications
    clann_key_type status;
};

/**
 *
 */
struct node
{
    clann_id_type id;
    clann_real_type clustering;
    void *info; // used by external libraries and applications
    void *attr; // used by external libraries and applications
    clann_key_type status;
};

/**
 *
 */
struct adjacency
{
    struct node *n;
    struct edge *e;
};

/**
 * Graph structure
 */
struct graph
{
    clann_uint_type n_node;
    clann_uint_type n_edge;
    clann_list_type *l_node;
    clann_list_type *l_edge;
    clann_bool_type directed;
    clann_real_type clustering;

    /**
     * The adjacency list is indexed by the node's id.
     */
    clann_list_type **l_near;

    /**
     * This function tell if two nodes have the same information
     * (i.e. are equal).
     */
    clann_bool_type (*f_node_eq)(void *, void *);
};


/**
 * Initialize an given graph
 */
inline void
graph_initialize(struct graph *g);

/**
 * Finalize an given graph
 */
inline void
graph_finalize(struct graph *g);

/**
 * Creates a copy of a graph.
 *
 * @param ga    Pointer to a graph structure.
 * @param gb    Pointer to a uninitialized graph structure.
 * @return      Return 0 (zero) for error and 1 (one) for success.
 */
int
graph_copy(const struct graph *ga,
           struct graph *gb);

/**
 *
 */
void
graph_create_adjacency_list(struct graph *g);

/**
 *
 */
void
graph_destroy_adjacency_list(struct graph *g);

/**
 *
 */
struct edge *
graph_add_edge(struct graph *g,
               struct node *na,
               struct node *nb,
               void *info);

/**
 *
 */
struct node *
graph_add_node(struct graph *g,
               void *info);

/**
 *
 */
struct edge *
graph_get_edge(struct graph *g,
               clann_id_type id);

/**
 *
 */
struct edge *
graph_get_edge_by_nodes(struct graph *g,
                        struct node *na,
                        struct node *nb);

/**
 *
 */
clann_list_type *
graph_get_edges_by_node(struct graph *g,
                        struct node *n);

/**
 *
 */
clann_list_type *
graph_get_edge_list(struct graph *g);

/**
 *
 */
struct node *
graph_get_node(struct graph *g,
               clann_id_type id);

/**
 *
 */
struct node *
graph_get_node_by_info(struct graph *g,
                       void *info);

/**
 *
 */
clann_list_type *
graph_get_node_list(struct graph *g);

/**
 *
 */
clann_list_type *
graph_get_node_neighbors(struct graph *g,
                         struct node *n);

/**
 *
 */
clann_real_type
graph_clustering(struct graph *g);

/**
 *
 */
clann_real_type
graph_node_clustering(struct graph *g,
                      struct node *n);

/**
 *
 */
struct tree *
graph_spanning_tree(struct graph *g,
                    struct node *n);


#endif
