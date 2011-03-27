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

#include "gdraw.h"


/**
 * Main functions, not related to Gtk
 */

void
gdraw_initialize(struct gdraw *d)
{
    d->layout = radial;
    d->center.x = 0;
    d->center.y = 0;
    d->g = NULL;
}

void
gdraw_finalize(struct gdraw *d)
{
    free((void *) d);
}

void
gdraw_set_point_from_polar(gdraw_point_type *p,
                           clann_real_type r,
                           clann_real_type t)
{
    p->x = r * CLANN_COS(t);
    p->y = r * CLANN_SIN(t);
}

void
gdraw_set_graph(struct gdraw *d,
                struct graph *g)
{
    gdraw_edge_attr *e;
    gdraw_node_attr *n;
    clann_list_type *l;

    d->g = g;

    /**
     * Updating edges
     */
    l = graph_get_edge_list(g);

    while (l)
    {
        e = malloc(sizeof(gdraw_edge_attr));
        e->layout = direct;
        ((struct edge *) l->info)->attr = e;

        l = l->next;
    }

    /**
     * Updating nodes
     */
    l = graph_get_node_list(g);

    while (l)
    {
        n = malloc(sizeof(gdraw_node_attr));
        n->point.x = 0;
        n->point.y = 0;
        n->range.x = 0;
        n->range.y = 0;
        ((struct node *) l->info)->attr = n;

        l = l->next;
    }
}

void
gdraw_draw_edge(struct edge *e,
                cairo_t *c)
{
    gdraw_node_attr *aa = (gdraw_node_attr *) e->na->attr;
    gdraw_node_attr *ba = (gdraw_node_attr *) e->nb->attr;
    gdraw_edge_attr *a = (gdraw_edge_attr *) e->attr;

    cairo_set_source_rgb(c, GDRAW_EDGE_COLOR);
    cairo_set_line_width(c, GDRAW_EDGE_WIDTH);

    switch (a->layout)
    {
        case arc:
            break;
        case direct:
            cairo_move_to(c, aa->point.x, aa->point.y);
            cairo_line_to(c, ba->point.x, ba->point.y);
            break;
        case semicircle:
            break;
    }

    cairo_stroke(c);
}

void
gdraw_draw_node(struct node *n,
                cairo_t *c)
{
    gdraw_node_attr *a = (gdraw_node_attr *) n->attr;

    cairo_set_source_rgb(c, GDRAW_NODE_COLOR);
    cairo_arc(c, a->point.x, a->point.y, GDRAW_NODE_WIDTH, 0, 2 * M_PI);
    cairo_fill_preserve(c);
    cairo_set_source_rgb(c, GDRAW_LINE_COLOR);
    cairo_set_line_width(c, GDRAW_LINE_WIDTH);
    cairo_stroke(c);
}

void
gdraw_draw_radial_layout(struct gdraw *d,
                         cairo_t *c)
{
    /**
     * Searching for the best node to be the root o the graph spanning tree
     */
    clann_list_type *l;

    l = graph_get_node_list(d->g);

    while (l)
    {
        //

        l = l->next;
    }
}

void
gdraw_draw_spread_layout(struct gdraw *d,
                         cairo_t *c)
{
    clann_list_type *l;
    gdraw_node_attr *a;
    struct node *n;

    l = graph_get_node_list(d->g);

    while (l)
    {
        n = (struct node *) l->info;
        a = (gdraw_node_attr *) n->attr;

        a->point.x = clann_randint(GDRAW_SIDE_SPACE,
                                   d->size.x - GDRAW_SIDE_SPACE);
        a->point.y = clann_randint(GDRAW_SIDE_SPACE,
                                   d->size.y - GDRAW_SIDE_SPACE);

        l = l->next;
    }
}

void
gdraw_draw_circle_layout(struct gdraw *d,
                         cairo_t *c)
{
    clann_real_type theta, radius, space;
    clann_size_type size = d->g->n_node;
    clann_list_type *l;
    gdraw_node_attr *a;
    struct node *n;

    radius = d->center.y - GDRAW_SIDE_SPACE;
    space = 2 * M_PI / size;
    theta = 0;

    l = graph_get_node_list(d->g);

    while (l)
    {
        n = (struct node *) l->info;
        a = (gdraw_node_attr *) n->attr;

        gdraw_set_point_from_polar(&a->point, radius, theta);
        a->point.x += d->center.x;
        a->point.y += d->center.y;
        theta += space;

        l = l->next;
    }
}

void
gdraw_draw(struct gdraw *d,
           cairo_t *c)
{
    clann_list_type *l;

    cairo_set_source_rgb(c, GDRAW_SOFT_COLOR);
    cairo_set_line_width(c, GDRAW_SOFT_WIDTH);
    cairo_move_to(c,   0 + d->center.x,  10 + d->center.y);
    cairo_line_to(c,   0 + d->center.x, -10 + d->center.y);
    cairo_move_to(c, -10 + d->center.x,   0 + d->center.y);
    cairo_line_to(c,  10 + d->center.x,   0 + d->center.y);
    cairo_stroke(c);

    /**
     * Switch between graph drawing technics
     */
    switch (d->layout)
    {
        case radial:
            gdraw_draw_radial_layout(d, c);
            break;
        case spread:
            gdraw_draw_spread_layout(d, c);
            break;
        case circle:
            gdraw_draw_circle_layout(d, c);
            break;
    }

    /**
     * Draw edges
     */
    l = graph_get_edge_list(d->g);

    while (l)
    {
        gdraw_draw_edge((struct edge *) l->info, c);
        l = l->next;
    }

    /**
     * Draw edges
     */
    l = graph_get_node_list(d->g);

    while (l)
    {
        gdraw_draw_node((struct node *) l->info, c);
        l = l->next;
    }
}


/**
 * Starting gtk graph drawing port
 */

G_DEFINE_TYPE(GDrawGtk, gdraw_gtk, GTK_TYPE_DRAWING_AREA);

static gboolean
gdraw_gtk_expose(GtkWidget *w,
                 GdkEventExpose *e);

gboolean
gdraw_gtk_key_press(GtkWidget *w,
                    GdkEventKey *k);

static void
gdraw_gtk_class_init(GDrawGtkClass *d)
{
    GtkWidgetClass *w = GTK_WIDGET_CLASS(d);

    w->expose_event = gdraw_gtk_expose;
    w->key_press_event = gdraw_gtk_key_press;
}

static void
gdraw_gtk_init(GDrawGtk *w)
{
    gdraw_initialize(&(GDRAW_GTK_GET_CLASS(w)->gd));
}

GtkWidget *
gdraw_gtk_new(void)
{
    GtkWidget *w = g_object_new(GDRAW_GTK_TYPE, NULL);

    gtk_widget_add_events(w,
        (
        GDK_BUTTON_RELEASE_MASK |
        GDK_ENTER_NOTIFY |
        GDK_LEAVE_NOTIFY |
        GDK_MOTION_NOTIFY |
        GDK_KEY_PRESS_MASK |
        GDK_KEY_RELEASE_MASK |
        GDK_POINTER_MOTION_HINT_MASK |
        GDK_POINTER_MOTION_MASK |
        GDK_SCROLL_MASK
        )
    );

    GTK_WIDGET_SET_FLAGS(w, GTK_CAN_FOCUS);
    gtk_widget_grab_focus(w);

    return w;
}

static gboolean
gdraw_gtk_expose(GtkWidget *w,
                 GdkEventExpose *e)
{
    GDrawGtkClass *d = GDRAW_GTK_GET_CLASS(w);

    /**
     * Create a cairo context
     */
    cairo_t *c = gdk_cairo_create(w->window);

    cairo_rectangle(c, e->area.x, e->area.y, e->area.width, e->area.height);
    cairo_set_source_rgb(c, GDRAW_BACK_COLOR);
    cairo_fill(c);

    /**
     * Get the center and the size of the widget
     */
    d->gd.size.x = w->allocation.width;
    d->gd.size.y = w->allocation.height;

    d->gd.center.x = w->allocation.width / 2;
    d->gd.center.y = w->allocation.height / 2;

    if (d->gd.g)
        gdraw_draw(&d->gd, c);

    cairo_destroy(c);

    return FALSE;
}

gboolean
gdraw_gtk_key_press(GtkWidget *w,
                    GdkEventKey *k)
{
    printf("key_code: %d, key_val: %s\n",
            k->keyval,
            gdk_keyval_name(k->keyval));
    return FALSE;
}
