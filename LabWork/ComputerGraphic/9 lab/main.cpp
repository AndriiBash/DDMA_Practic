#include <iostream>
#include <cmath>
#include <GLUT/glut.h>

float a = 1.0f; // Параметр для x
float b = 1.0f; // Параметр для y
float rotationAngle = 0.0f; // Кут обертання

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(5.0 * sin(rotationAngle), 2.0, 5.0 * cos(rotationAngle), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(rotationAngle, 1.0, 1.0, 2.0); // Змінили ось обертання на y

    glColor3f(1.0, 1.0, 1.0);

    // Відображення еліптичного параболоїда
    glBegin(GL_POINTS);
    for (float x = -1.0; x <= 1.0; x += 0.01)
    {
        for (float y = -1.0; y <= 1.0; y += 0.01)
        {
            float z = pow(x,2) / (pow(a,2)) + pow(y,2) / (pow(b,2));
            glVertex3f(x, y, z);
        }
    }
    glEnd();

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle()
{
    rotationAngle += 0.01f;
    
    if (rotationAngle > 2 * M_PI)
    {
        rotationAngle -= 2 * M_PI;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Еліптичний параболоїд🇺🇦");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
