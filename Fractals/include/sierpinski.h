#ifndef SIERPINSKI_H
#define SIERPINSKI_H

#include <GL/glew.h>
#include "display.h"

using namespace std;

typedef struct Point
{
    float x;
    float y;
} point;

class Sierpinski
{
public:
    Sierpinski(unsigned int nIter);

    void DrawSierpinskiCarpet();

    void DrawSierpinskiTriangle();

    virtual ~Sierpinski();
protected:
    void drawSubTriangle(unsigned int n, point A, point B, point C);
    void drawSubSquare(unsigned int n, point A, point B, point C, point D);
private:
    Display *sDisplay;
    unsigned int numIteration;
};

#endif // SIERPINSKI_H
