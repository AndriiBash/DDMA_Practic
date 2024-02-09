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

#define xMin -4.0
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
    
    const int numVertices = 10;

    glBegin(GL_LINE_LOOP);

    double centerX = 0.0;
    double centerY = 0.0;
    double outerRadius = 0.4;
    double innerRadius = 0.2;

    glColor3f(1.0, 0.5, 0.8);

    for (int i = 0; i < numVertices; ++i)
    {
        double angleOuter = i * 2.0 * M_PI / numVertices;
        double angleInner = (i + 0.5) * 2.0 * M_PI / numVertices;

        double xOuter = centerX + outerRadius * cos(angleOuter);
        double yOuter = centerY + outerRadius * sin(angleOuter);

        double xInner = centerX + innerRadius * cos(angleInner);
        double yInner = centerY + innerRadius * sin(angleInner);

        glVertex2d(xOuter, yOuter);
        glVertex2d(xInner, yInner);
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
