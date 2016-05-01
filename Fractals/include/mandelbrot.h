#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "display.h"
#include <GL/glew.h>
#include "color.h"

using namespace std;

class Mandelbrot
{
public:
    Mandelbrot(unsigned int numIteration);

    void Draw2Dmandelbrot();

    void Draw3Dmandelbrot();

    virtual ~Mandelbrot();
private:
    Display *mDisplay;
    unsigned int numIteration;
    double pr, pi;
    double newRe, newIm, oldRe, oldIm;
    double zoom,moveX,moveY;

};

#endif // MANDELBROT_H
