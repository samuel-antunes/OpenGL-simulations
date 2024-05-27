#ifndef NBODY_H
#define NBODY_H

typedef struct {
    float x, y;  
    float vx, vy;  
    float ax, ay; 
    float radius;
} Particle;

typedef struct {
    Particle *particles;
    int num_particles;
    int max_particles;
} Universe;

void init_particles(Universe *universe, int num_particles);
void update_particles(Universe *universe, double dt);
void calculate_forces(Universe *universe);
void calculate_gravity_forces(Universe *universe);
void calculate_collision_forces(Universe *universe);

#endif

