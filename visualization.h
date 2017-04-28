#ifndef VIS_H
#define VIS_H

#define _USE_MATH_DEFINES
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cmath>

//http://stackoverflow.com/questions/5988686/creating-a-3d-sphere-in-opengl-using-visual-c
// your framework of choice here

class SolidSphere
{
protected:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;

public:
    SolidSphere(float radius, unsigned int rings, unsigned int sectors);

    void draw(GLfloat x, GLfloat y, GLfloat z);

    void display();

    
};

#endif

