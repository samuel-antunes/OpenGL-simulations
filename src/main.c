#include <GL/glut.h>
#include "graphics.h"
#include "nbody.h"

Universe universe;

// Timer settings
#define DELTA_TIME 0.01
#define TIMER_MS 16 // approximately 60 FPS

void update(int value) {
    update_particles(&universe, DELTA_TIME);
    glutPostRedisplay(); // Mark the current window as needing to be redisplayed
    glutTimerFunc(TIMER_MS, update, 0); // Set up next timer
}

void display() {
    draw_particles(&universe);
}

void init() {
    init_graphics();
    init_particles(&universe, 1000);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480); // Set the window size
    glutInitWindowPosition(100, 100); // Set the window position
    glutCreateWindow("N-body Simulator"); // Create the window with a title

    init(); // Initialize the simulation and graphics settings

    glutDisplayFunc(display); // Set the display callback for the current window
    glutTimerFunc(TIMER_MS, update, 0); // Set the first timer

    glutMainLoop(); // Enter the GLUT event processing loop

    return 0;
}

