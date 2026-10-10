#include <GL/glut.h>
#include <cmath>

float shipX = -60.0f;
float waveOffset = 0.0f;
float cloudX = 0.0f;

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();
}

void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 25);
    drawCircle(x + 25, y + 15, 30);
    drawCircle(x + 55, y, 25);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // SKY
    glColor3f(0.53f, 0.81f, 0.98f);
    glBegin(GL_QUADS);
    glVertex2f(0, 300);
    glVertex2f(800, 300);
    glVertex2f(800, 600);
    glVertex2f(0, 600);
    glEnd();

    // SEA
    glColor3f(0.0f, 0.0f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(800, 0);
    glVertex2f(800, 300);
    glVertex2f(0, 300);
    glEnd();

    // SUN
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(650, 500, 50);

    // MOVING CLOUDS
    drawCloud(100 + cloudX, 500);
    drawCloud(350 + cloudX, 450);

    // WAVES
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int y = 80; y <= 220; y += 30) {
        glBegin(GL_LINE_STRIP);
        for (int x = 0; x <= 800; x++) {
            float waveY = y + 5 * sin((x + waveOffset) * 0.05f);
            glVertex2f(x, waveY);
        }
        glEnd();
    }

    // SHIP
    glPushMatrix();
    glTranslatef(shipX, 0.0f, 0.0f);

    // Hull
    glColor3f(0.5f, 0.3f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(250, 180);
    glVertex2f(500, 180);
    glVertex2f(550, 230);
    glVertex2f(200, 230);
    glEnd();

    // Deck
    glColor3f(0.8f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(300, 230);
    glVertex2f(450, 230);
    glVertex2f(450, 290);
    glVertex2f(300, 290);
    glEnd();

    // Chimney
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(380, 290);
    glVertex2f(420, 290);
    glVertex2f(420, 350);
    glVertex2f(380, 350);
    glEnd();

    // Mast
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(280, 230);
    glVertex2f(280, 400);
    glEnd();

    // Sail
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(280, 400);
    glVertex2f(280, 250);
    glVertex2f(370, 325);
    glEnd();

    // STICKMAN
    // Head
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(350, 320, 12);

    // Body, Arms + Legs
    glBegin(GL_LINES);
    // Body
    glVertex2f(350, 308);
    glVertex2f(350, 270);
    // Left Arm
    glVertex2f(350, 295);
    glVertex2f(335, 285);
    // Right Arm
    glVertex2f(350, 295);
    glVertex2f(365, 285);
    // Left Leg
    glVertex2f(350, 270);
    glVertex2f(340, 250);
    // Right Leg
    glVertex2f(350, 270);
    glVertex2f(360, 250);
    glEnd();

    glPopMatrix();
    glFlush();
}

void timer(int value) {
    shipX += 1.5f;
    waveOffset += 2.0f;
    cloudX += 0.2f;
    if (shipX > 850)
        shipX = -600;
    if (cloudX > 900)
        cloudX = -500;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void init() {
    glClearColor(0.8f, 0.9f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 600);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ship Sailing on the Sea");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
