#include <iostream>
#include <math.h>
#include <GLUT/glut.h>

float angle = 0.0;  // Кут обертання бублика

void renderTorus()
{
    // Встановлюємо положення джерела світла
    GLfloat light_position[] = { 1.0, 1.0, 2.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    // Увімкнення освітлення
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Налаштовуємо параметри матеріалу для кільця
    GLfloat ambient[] = { 0.64, 0.16, 0.16, 1.0 };  // Коричневий колір
    GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat shininess = 0.0;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    //glColor3f(1.0, 0.0, 0.0);  // Червоний колір для кільця
    
    glPushMatrix();  // Зберігаємо поточну матрицю
    glTranslated(2.0, 2.0, 0.0);  // Переміщуємо кільце
    glRotated(angle, 0.0, 1.0, 0.0);  // Обертаємо кільце навколо Y-осі
    glutSolidTorus(0.2, 0.5, 50, 50);  // Малюємо кільце (тор)
    glPopMatrix();  // Відновлюємо матрицю
    
    // Вимкнення освітлення
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    // Встановлюємо тривимірну проєкцію
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Встановлення камери
    gluLookAt(3.0, 3.0, 5.0, 2.0, 2.0, 0.0, 0.0, 1.0, 0.0);

    // Додано малювання бублика (tora)
    renderTorus();

    glFlush();
}

void update(int value)
{
    angle += 1.0;  // Збільшуємо кут обертання
    if (angle >= 360.0)
    {
        angle -= 360.0;  // Зациклюємо кут обертання
    }

    glutPostRedisplay();  // Перемальовуємо сцену
    glutTimerFunc(16, update, 0);  // Встановлюємо таймер для оновлення анімації
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Обертається бублик, та до чого він вертеться");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(renderScene);

    // Таймер анімації
    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}
