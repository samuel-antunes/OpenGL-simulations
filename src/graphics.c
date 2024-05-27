#include "graphics.h"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

float zoomFactor = 1.0;

void init_graphics() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0 * zoomFactor, (640.0 / 480.0), 1.0, 1000.0);  // Adjust FOV based on zoomFactor

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(320.0, 240.0, 500.0,  // Camera position (x, y, z)
              320.0, 240.0, 0.0,    // Look at center (x, y, z)
              0.0, 1.0, 0.0);       // Up vector (x, y, z)
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

void add_particle(Universe *universe, float x, float y) {
    if (universe->num_particles >= universe->max_particles) {
        // Optionally, resize the particles array or handle the error
        printf("Maximum number of particles reached.\n");
        return;
    }

    // Initialize the new particle
    Particle newParticle;
    newParticle.x = x;
    newParticle.y = y;
    newParticle.vx = 0;  // Initial velocity x
    newParticle.vy = 0;  // Initial velocity y

    // Add the new particle to the universe
    universe->particles[universe->num_particles] = newParticle;
    universe->num_particles++;  // Increment the count of particles
}
