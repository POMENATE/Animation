#ifndef JULIA_H
#define JULIA_H

#include <GL/glew.h>
#include <string>
#include <cmath>
#include <iomanip>
#include "color.h"
#include "display.h"

using namespace std;

class Julia
{
public:
    Julia(unsigned int maxIteration);

    void Draw2DjuliaSet();

    void Draw3DjuliaSet();

    virtual ~Julia();
private:
    Display *jDisplay;
    unsigned int numIteration;
    double cRe, cIm;
    double newRe, newIm, oldRe, oldIm;
    double zoom,moveX,moveY;
};

#endif // JULIA_H
