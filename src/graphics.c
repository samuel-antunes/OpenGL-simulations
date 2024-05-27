#include "graphics.h"
#include <GL/glut.h>
#include <math.h>

void init_graphics() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0 * 1.5, 0.0, 480.0 * 1.5);  // Adjust these values to zoom out
    glMatrixMode(GL_MODELVIEW);
}

void draw_particles(const Universe *universe) {
    int num_segments = 20; // Number of segments to approximate a circle
    float radius = 2.5; // Radius of the circle

    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
    glColor3f(1.0, 1.0, 1.0); // Set the color to white

    for (int i = 0; i < universe->num_particles; i++) {
        float cx = universe->particles[i].x;
        float cy = universe->particles[i].y;

        glBegin(GL_POLYGON);
        for(int j = 0; j < num_segments; j++) {
            float theta = 2.0f * 3.1415926f * (float)j / (float)num_segments; // Correct casting
            float x = radius * cosf(theta); // Calculate the x component
            float y = radius * sinf(theta); // Calculate the y component
            glVertex2f(x + cx, y + cy); // Output vertex
        }
        glEnd();
    }

    glFlush(); // Ensure all OpenGL commands are executed
}
