#include "mandelbrot.h"

Mandelbrot::Mandelbrot(unsigned int numIteration)
{
    mDisplay = new Display(400, 600, "Mandelbrot Set");
    this->numIteration = numIteration;
    newRe = 0;
    newIm = 0;
    oldRe = 0;
    oldIm = 0;
    zoom = 1.0;
    moveX = 0.0;
    moveY = 0.0;
}

Mandelbrot::~Mandelbrot()
{
    delete mDisplay;
}

void Mandelbrot::Draw2Dmandelbrot()
{
    unsigned int h, w;
    float xPoint, yPoint;

    mDisplay->getWindowSize(&w, &h);
    float xRatio = w/2, yRatio = h/2;

    glViewport(0,0,w,h);
    glOrtho(-1.0, 1.0,-1.0,1.0,1.0,1.0);

    while(!mDisplay->IsClosed())
    {
        glClearColor(0.2f , 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POINTS);
        for(unsigned int y = 0; y < h; y++)
        {
            for(unsigned int x = 0; x < w; x++)
            {

                pr = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
                pi = (y - h / 2) / (0.5 * zoom * h) + moveY;
                newRe = newIm = oldRe = oldIm = 0;

                unsigned int i;

                for(i = 0; i < numIteration; i++)
                {

                    oldRe = newRe;
                    oldIm = newIm;

                    newRe = oldRe * oldRe - oldIm * oldIm + pr;
                    newIm = 2 * oldRe * oldIm + pi;

                    if((newRe * newRe + newIm * newIm) > 4) break;
                }
                xPoint = (-(1-((float)x/xRatio)));
                yPoint = (-(1-((float)y/yRatio)));
                hsv cVal;
                cVal.h = i%256;
                cVal.s=200;
                cVal.v=255*(i < numIteration);
                rgb color = hsv2rgb(cVal);

                glColor3f(color.r, color.g, color.b);
                glVertex2f(xPoint,yPoint);
                glVertex2f(-xPoint,-yPoint);
                glVertex2f(xPoint,-yPoint);
                glVertex2f(-xPoint,yPoint);
            }
        }
        glEnd();
        glFlush();
        mDisplay->swapBuffer();
    }
}

void Mandelbrot::Draw3Dmandelbrot()
{

}
