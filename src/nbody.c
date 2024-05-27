#include "nbody.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void init_particles(Universe *universe, int num_particles) {
    srand(time(NULL));  // Seed the random number generator
    universe->num_particles = num_particles;
    universe->max_particles = 300;
    universe->particles = malloc(sizeof(Particle) * universe->max_particles);

    float centerX = 320;  // Center of the distribution
    float centerY = 240;
    float maxRadius = 200;  // Maximum radius of particle distribution

    for (int i = 0; i < num_particles; i++) {
        float angle = (float)rand() / RAND_MAX * 2 * M_PI;  // Random angle
        float radius = sqrt((float)rand() / RAND_MAX) * maxRadius;  // Square root increases density towards center

        universe->particles[i].x = centerX + radius * cos(angle);  // Convert polar to Cartesian coordinates
        universe->particles[i].y = centerY + radius * sin(angle);
        universe->particles[i].vx = (rand() % 100 - 50) / 10.0;  // Random x velocity
        universe->particles[i].vy = (rand() % 100 - 50) / 10.0;  // Random y velocity
        universe->particles[i].ax = 0;  // Initial x acceleration
        universe->particles[i].ay = 0;  // Initial y acceleration
    }
}

void update_particles(Universe *universe, double dt) {
    for (int i = 0; i < universe->num_particles; i++) {
        // Update velocities
        universe->particles[i].vx += universe->particles[i].ax * dt;
        universe->particles[i].vy += universe->particles[i].ay * dt;

        // Update positions
        universe->particles[i].x += universe->particles[i].vx * dt;
        universe->particles[i].y += universe->particles[i].vy * dt;

        // Reset accelerations
        universe->particles[i].ax = 0;
        universe->particles[i].ay = 0;
    }
}

void calculate_gravity_forces(Universe *universe) {
    float G = 100;  // Adjusted gravitational constant for visible effects
    float softening = 1e-12;  // Reduced softening term

    // Reset accelerations for gravity calculation
    for (int i = 0; i < universe->num_particles; i++) {
        universe->particles[i].ax = 0;
        universe->particles[i].ay = 0;
    }

    // Compute gravitational force
    for (int i = 0; i < universe->num_particles; i++) {
        for (int j = i + 1; j < universe->num_particles; j++) {
            float dx = universe->particles[j].x - universe->particles[i].x;
            float dy = universe->particles[j].y - universe->particles[i].y;
            float distSq = dx * dx + dy * dy + softening;
            float dist = sqrt(distSq);
            float invDist3 = pow(distSq, -1.5);
            float force = G * invDist3;

            universe->particles[i].ax += force * dx;
            universe->particles[i].ay += force * dy;
            universe->particles[j].ax -= force * dx;
            universe->particles[j].ay -= force * dy;
        }
    }
}

void calculate_collision_forces(Universe *universe) {
    float efficiency = 0.8;  // 80% efficiency in velocity transfer

    // Compute collision forces
    for (int i = 0; i < universe->num_particles; i++) {
        for (int j = i + 1; j < universe->num_particles; j++) {
            float dx = universe->particles[j].x - universe->particles[i].x;
            float dy = universe->particles[j].y - universe->particles[i].y;
            float dist = sqrt(dx * dx + dy * dy);

            if (dist < (universe->particles[i].radius + universe->particles[j].radius)) {
                float nx = dx / dist;
                float ny = dy / dist;
                float rvx = universe->particles[j].vx - universe->particles[i].vx;
                float rvy = universe->particles[j].vy - universe->particles[i].vy;
                float impulse = (1 + efficiency) * (rvx * nx + rvy * ny) / (1 / universe->particles[i].radius + 1 / universe->particles[j].radius);

                universe->particles[i].vx -= impulse * nx / universe->particles[i].radius;
                universe->particles[i].vy -= impulse * ny / universe->particles[i].radius;
                universe->particles[j].vx += impulse * nx / universe->particles[j].radius;
                universe->particles[j].vy += impulse * ny / universe->particles[j].radius;
            }
        }
    }
}

void calculate_forces(Universe *universe) {
    calculate_gravity_forces(universe);
    calculate_collision_forces(universe);
}

void free_universe(Universe *universe) {
    free(universe->particles);
}
