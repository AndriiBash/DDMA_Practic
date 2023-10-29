//
//  main.cpp
//  OpenGLC++
//
//  Created by Андрiй on 26.10.2023.
//

#include <iostream>
#include <math.h>
#include <iomanip>
#include <sstream>
#include <GLUT/glut.h>

#define xMin -2.0
#define xMax 4.0
#define xStep 0.1

void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Малювання ліній координати
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    glVertex2d(xMin, 0.0);
    glVertex2d(xMax, 0.0);
    glVertex2d(0.0, xMin - 1);
    glVertex2d(0.0, xMax + 1);
    glEnd();

    // Додавання надписей для лінії коордиант x
    glColor3f(1.0, 1.0, 1.0);
    for (double x = xMin; x <= xMax; x += 0.5)
    {
        glRasterPos2d(x, -0.2);  // Координати тексту

        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << round(x * 10) / 10.0;
        
        std::string label = ss.str();
        
        for (char c : label)
        {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);  // Реднер тексту
        }
        
        // Малювання лінії для відмітки
        glBegin(GL_LINES);
        glVertex2d(x, 0.05);
        glVertex2d(x, -0.05);
        glEnd();
    }
    
    // Додавання надписей для лінії коордиант y
    for (double y = xMin - 1; y <= xMax + 1; y += 0.5)
    {
        if (y < 0)
        {
            glRasterPos2d(-0.3, y);
        }
        else
        {
            glRasterPos2d(-0.25, y);
        }
        
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << round(y * 10) / 10.0;
        
        std::string label = ss.str();
        
        for (char c : label)
        {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);  // Rendering text
        }
        
        // Малювання лінії для відмітки
        glBegin(GL_LINES);
        glVertex2d(0.035, y);
        glVertex2d(-0.035, y);
        glEnd();
    }
    
    // Малювання графіка
    glColor3f(1.0, 0.25, 1.0);
    glBegin(GL_LINE_STRIP);
    for (double x = xMin; x <= xMax; x += xStep)
    {
        double y = 3 * pow(x, 2) - pow(x, 3);
        glVertex2d(x, y);
    }

    glEnd();
    
    glFlush();
}

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL на macOS🇺🇦");
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xMin, xMax, xMin - 1, xMax + 1); // Ортогональна проєкція
    glMatrixMode(GL_MODELVIEW);
    
    glutDisplayFunc(renderScene);
    glutMainLoop();
    
    return 0;
}
