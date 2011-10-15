/**
 * Copyright (C) 2008-2011 Joao Paulo de Souza Medeiros.
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

#include <stdlib.h>
#include <unistd.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <pthread.h>
#include "../code/som.h"
#include "../code/clann.h"
#include "../code/matrix.h"
#include "../code/reader.h"


#define X           0
#define Y           1
#define Z           2

#define MESH        0
#define POINTS      1
#define INPUT       2
#define AXIS        3

#define USAGE "Usage: som.o <training-file>\n"\
              "             <mesh-type>\n"\
              "             <width>\n"\
              "             <start-epoch>\n"\
              "             <end-epoch>\n"


unsigned int show[4] = {1, 1, 1, 1};
unsigned int epochs;
int axis_y, axis_x, axis_z;
char *file;
struct matrix x, a;
struct som ann;
pthread_t thread;


void
cb_display(void)
{
    unsigned int i, j;
    clann_real_type *w;

    glPushMatrix();

    glRotatef((GLfloat) axis_z, 0.0, 0.0, 1.0);
    glRotatef((GLfloat) axis_y, 0.0, 1.0, 0.0);
    glRotatef((GLfloat) axis_x, 1.0, 0.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT);

    if (show[AXIS])
    {
        glTranslatef(-1.0, -1.0, -1.0);
        glLineWidth(1.0);
 
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_STRIP);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.5, 0.0, 0.0);
        glEnd();
 
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_STRIP);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 0.5, 0.0);
        glEnd();
 
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINE_STRIP);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 0.0, 0.5);
        glEnd();
 
        glTranslatef(1.0, 1.0, 1.0);
    }

    /**
     * Display input set
     */
    glColor3f(0.6, 0.6, 0.6);
    glPointSize(1.0);

    if (show[INPUT])
    {
        glBegin(GL_POINTS);

        for (i = 0; i < x.rows; i++)
        {
            glVertex3f((GLfloat) *matrix_value(&x, i, X),
                       (GLfloat) *matrix_value(&x, i, Y),
                       (GLfloat) *matrix_value(&x, i, Z));
        }

        glEnd();
    }

    /**
     * Display the connections of SOM
     *
    if (show[MESH])
    {
        glColor3f(0.0, 0.0, 0.0);
        glPointSize(1.0);
        glLineWidth(2.0);

        for (i = 0; i < ann.grid.x_len; i++)
        {
            glBegin(GL_LINE_STRIP);

            for (j = 0; j < ann.grid.y_len; j++)
            {
                w = som_grid_get_weights(&ann.grid, i, j);
                glVertex3f((GLfloat) w[X],
                           (GLfloat) w[Y],
                           (GLfloat) w[Z]);
            }

            glEnd();
        }

        for (i = 0; i < ann.grid.y_len; i++)
        {
            glBegin(GL_LINE_STRIP);

            for (j = 0; j < ann.grid.x_len; j++)
            {
                w = som_grid_get_weights(&ann.grid, j, i);
                glVertex3f((GLfloat) w[X],
                           (GLfloat) w[Y],
                           (GLfloat) w[Z]);
            }

            glEnd();
        }
    }*/

    /**
     * Display the output neurons
     */
    if (show[POINTS])
    {
        glPointSize(3.0);
        glLineWidth(1.0);

        glBegin(GL_POINTS);

        for (j = 0; j < ann.grid.n_neurons; j++)
        {
            w = matrix_value(&ann.grid.weights, j, 0);

            glVertex3f((GLfloat) w[X],
                       (GLfloat) w[Y],
                       (GLfloat) w[Z]);
        }

        glEnd();
    }

    glPopMatrix();
    glutSwapBuffers();
}

void
init(void) 
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.7, 1.7, -1.7, 1.7, -1.7, 1.7);
    glEnable(GL_CULL_FACE);
}

void
cb_idle(void)
{
    glutPostRedisplay();
}

void
cb_keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'a':
            show[AXIS] = !show[AXIS];
            break;

        case 'p':
            show[POINTS] = !show[POINTS];
            break;

        case 'm':
            show[MESH] = !show[MESH];
            break;

        case 'i':
            show[INPUT] = !show[INPUT];
            break;

        case 'x':
            axis_x = (axis_x - 5) % 360;
            glutPostRedisplay();
            break;

        case 'X':
            axis_x = (axis_x + 5) % 360;
            glutPostRedisplay();
            break;

        case 'y':
            axis_y = (axis_y + 5) % 360;
            glutPostRedisplay();
            break;

        case 'Y':
            axis_y = (axis_y - 5) % 360;
            glutPostRedisplay();
            break;

        case 'z':
            axis_z = (axis_z - 5) % 360;
            glutPostRedisplay();
            break;

        case 'Z':
            axis_z = (axis_z + 5) % 360;
            glutPostRedisplay();
            break;

        case '0':
            axis_x = 0;
            axis_y = 0;
            axis_z = 0;
            glutPostRedisplay();
            break;
    }
}

void*
training_thread(void *arg)
{
    som_train_incremental(&ann, &x, epochs);

    return NULL;
}

int
main(int argc, char *argv[])
{
    if (argc == 6)
    {
        clann_initialize();

        reader_read_data_file(argv[1], &x);
        clann_size_type width = atoi(argv[3]);
        ann.epoch = atoi(argv[4]);
        epochs = atoi(argv[5]);

        som_initialize(&ann, atoi(argv[2]), x.cols, width);
        ann.step = 100;

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(0, 0);
        glutCreateWindow("SOM ISN Training");
        init();
        glutDisplayFunc(cb_display);
        glutIdleFunc(cb_idle);
        glutKeyboardFunc(cb_keyboard);

        pthread_create(&thread, NULL, training_thread, (void *) NULL);

        glutMainLoop();
    }
    else
    {
        printf(USAGE);

        return 1;
    }

    return 0;
}
