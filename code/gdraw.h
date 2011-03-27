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

#ifndef GDRAW_H
#define GDRAW_H

#include <math.h>
#include <gtk/gtk.h>
#include "clann.h"
#include "graph.h"

#define GDRAW_BACK_COLOR    1.0, 1.0, 1.0
#define GDRAW_EDGE_COLOR    0.0, 0.0, 0.0
#define GDRAW_NODE_COLOR    0.9, 0.9, 0.9
#define GDRAW_LINE_COLOR    0.0, 0.0, 0.0
#define GDRAW_SOFT_COLOR    0.7, 0.7, 0.7
#define GDRAW_TEXT_COLOR    0.0, 0.0, 0.0

#define GDRAW_EDGE_WIDTH    1
#define GDRAW_LINE_WIDTH    2
#define GDRAW_SOFT_WIDTH    1
#define GDRAW_NODE_WIDTH    3

#define GDRAW_SIDE_SPACE    10

typedef enum {spread, radial, circle} gdraw_layout_type;
typedef enum {arc, direct, semicircle} gdraw_edge_layout_type;

typedef struct
{
    clann_real_type x;
    clann_real_type y;
} gdraw_point_type;

typedef struct
{
    gdraw_point_type point;
    gdraw_point_type range;
    gdraw_point_type space;
    clann_bool_type flag;
    clann_real_type depth;
} gdraw_node_attr;

typedef struct
{
    gdraw_edge_layout_type layout;
} gdraw_edge_attr;

/**
 *
 */
struct gdraw
{
    gdraw_point_type size;
    gdraw_point_type center;
    gdraw_layout_type layout;
    struct graph *g;
};


/**
 *
 */
void
gdraw_set_point_from_polar(gdraw_point_type *p,
                           clann_real_type r,
                           clann_real_type t);

/**
 *
 */
void
gdraw_initialize(struct gdraw *d);

/**
 *
 */
void
gdraw_finalize(struct gdraw *d);

/**
 *
 */
void
gdraw_set_graph(struct gdraw *d,
                struct graph *g);

/**
 *
 */
void
gdraw_draw_edge(struct edge *e,
                cairo_t *c);

/**
 *
 */
void
gdraw_draw_node(struct node *n,
                cairo_t *c);

/**
 *
 */
void
gdraw_draw_radial_layout(struct gdraw *d,
                         cairo_t *c);

/**
 *
 */
void
gdraw_draw_spread_layout(struct gdraw *d,
                         cairo_t *c);

/**
 *
 */
void
gdraw_draw_circle_layout(struct gdraw *d,
                         cairo_t *c);

/**
 *
 */
void
gdraw_draw(struct gdraw *d,
           cairo_t *c);

/**
 * Starting gdraw gtk port
 */

G_BEGIN_DECLS

#define GDRAW_GTK_TYPE          (gdraw_gtk_get_type())
#define GDRAW_GTK(o)            \
    (G_TYPE_CHECK_INSTANCE_CAST((o),GDRAW_GTK_TYPE,GDrawGtk))
#define GDRAW_GTK_CLASS(o)      \
    (G_TYPE_CHECK_CLASS_CAST((o),GDRAW_GTK,GDrawGtkClass))
#define IS_GDRAW_GTK(o)	        \
    (G_TYPE_CHECK_INSTANCE_TYPE((o),GDRAW_GTK_TYPE))
#define IS_GDRAW_GTK_CLASS(o)   (G_TYPE_CHECK_CLASS_TYPE((o),GDRAW_GTK_TYPE))
#define GDRAW_GTK_GET_CLASS(o)  \
    (G_TYPE_INSTANCE_GET_CLASS((o),GDRAW_GTK_TYPE,GDrawGtkClass))


typedef struct _GDrawGtk GDrawGtk;
typedef struct _GDrawGtkClass GDrawGtkClass;

struct _GDrawGtk
{
    GtkDrawingArea parent;
};

struct _GDrawGtkClass
{
    GtkDrawingAreaClass parent_class;
    struct gdraw gd;
};


/**
 *
 */
GtkWidget *
gdraw_gtk_new(void);


G_END_DECLS


#endif
