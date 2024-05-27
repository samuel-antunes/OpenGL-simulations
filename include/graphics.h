#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "nbody.h"  // Include the universe definition

void init_graphics();
void draw_particles(const Universe *universe);
void add_particle(Universe *universe, float x, float y);

#endif

