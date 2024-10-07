#include <GL/glut.h>
#include <math.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw night sky
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.2); // Dark blue
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();

    // Draw moon
    glColor3f(1.0, 1.0, 0.8); // Light yellow
    float moonX = 0.6, moonY = 0.8, moonRadius = 0.1;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(moonX, moonY);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = cosf(angle) * moonRadius;
        float dy = sinf(angle) * moonRadius;
        glVertex2f(moonX + dx, moonY + dy);
    }
    glEnd();

    // Draw river
    glColor3f(0.0, 0.5, 1.0); // Blue
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -0.5);
    glVertex2f(1.0, -0.5);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();

    // Draw tree trunk
    glColor3f(0.55, 0.27, 0.07); // Brown
    glBegin(GL_QUADS);
    glVertex2f(-0.8, -0.5);
    glVertex2f(-0.7, -0.5);
    glVertex2f(-0.7, -0.2);
    glVertex2f(-0.8, -0.2);
    glEnd();

    // Draw tree leaves
    glColor3f(0.0, 0.8, 0.0); // Green
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.85, -0.2);
    glVertex2f(-0.75, 0.1);
    glVertex2f(-0.65, -0.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.85, -0.1);
    glVertex2f(-0.75, 0.2);
    glVertex2f(-0.65, -0.1);
    glEnd();

    // Draw vegetation
    glColor3f(0.0, 0.5, 0.0); // Dark green
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.9, -0.5);
    glVertex2f(-0.85, -0.4);
    glVertex2f(-0.8, -0.5);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.7, -0.5);
    glVertex2f(-0.65, -0.4);
    glVertex2f(-0.6, -0.5);
    glEnd();


// Desenha nuvens
glColor3f(1.0, 1.0, 1.0); // Branco

// Função auxiliar para desenhar um círculo
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float angle = 2.0f * 3.1415926f * i / num_segments;
        float dx = cosf(angle) * r;
        float dy = sinf(angle) * r;
        glVertex2f(cx + dx, cy + dy);
    }
    glEnd();
}

// Parâmetros da nuvem
float cloudX = -0.5, cloudY = 0.7;
float cloudRadius1 = 0.1, cloudRadius2 = 0.12, cloudRadius3 = 0.08;

// Desenha círculos sobrepostos para formar a nuvem
drawCircle(cloudX, cloudY, cloudRadius1, 100);
drawCircle(cloudX + 0.1, cloudY + 0.05, cloudRadius2, 100);
drawCircle(cloudX + 0.2, cloudY, cloudRadius1, 100);
drawCircle(cloudX + 0.15, cloudY - 0.05, cloudRadius3, 100);
drawCircle(cloudX + 0.05, cloudY - 0.05, cloudRadius3, 100);

// Desenha outra nuvem
cloudX = -0.4;
drawCircle(cloudX, cloudY, cloudRadius1, 100);
drawCircle(cloudX + 0.1, cloudY + 0.05, cloudRadius2, 100);
drawCircle(cloudX + 0.2, cloudY, cloudRadius1, 100);
drawCircle(cloudX + 0.15, cloudY - 0.05, cloudRadius3, 100);
drawCircle(cloudX + 0.05, cloudY - 0.05, cloudRadius3, 100);

    glutSwapBuffers();
}

void init() {
    glClearColor(0.0, 0.0, 0.2, 1.0); // Dark blue background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("2D Night Scene");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}