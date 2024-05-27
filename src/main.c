#include <GL/glut.h>
#include "graphics.h"
#include "nbody.h"
#include <GL/freeglut.h>

Universe universe;
extern float zoomFactor;
// Timer settings
#define DELTA_TIME 0.01
#define TIMER_MS 16

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert screen coordinates to world coordinates
        float worldX = x;  // Adjust as necessary
        float worldY = 480 - y;  // Adjust as necessary, assuming window height is 480

        // Add a new particle at (worldX, worldY)
        add_particle(&universe, worldX, worldY);
        glutPostRedisplay();  // Redraw the scene
    }
}

void mouseWheel(int wheel, int direction, int x, int y) {
    if (direction > 0) {
        zoomFactor *= 1.1;  // Zoom in
    } else {
        zoomFactor /= 1.1;  // Zoom out
    }

    // Update the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0 * zoomFactor, (640.0 / 480.0), 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);

    glutPostRedisplay();  // Redraw the scene
}

void update(int value) {
    update_particles(&universe, DELTA_TIME);
    glutPostRedisplay();
    glutTimerFunc(TIMER_MS, update, 0);
}

void display() {
    draw_particles(&universe);
}

void init() {
    init_graphics();
    init_particles(&universe, 100);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("N-body Simulator");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouseButton);
    glutMouseWheelFunc(mouseWheel);
    glutTimerFunc(TIMER_MS, update, 0);

    glutMainLoop(); 

    return 0;
}

