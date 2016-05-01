#include "julia.h"

Julia::Julia(unsigned int maxIteration)
{
    jDisplay = new Display(400, 600, "Julia Set");
    numIteration = maxIteration;
    cRe = -0.75;
    cIm = 0.025015;
    newRe = 0;
    newIm = 0;
    oldRe = 0;
    oldIm = 0;
    zoom = 1.0;
    moveX = 0;
    moveY = 0;
}

Julia::~Julia()
{
    delete jDisplay;
}

void Julia::Draw2DjuliaSet()
{
    unsigned int h, w;
    float xPoint, yPoint;

    cout<<setprecision(3);

    jDisplay->getWindowSize(&w, &h);
    float xRatio = w/2, yRatio = h/2;

    glViewport(0,0,w,h);
    glOrtho(-1.0, 1.0,1.0,-1.0,0.0,0.0);

    while(!jDisplay->IsClosed())
    {
        glClearColor(0.2f , 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POINTS);
        for(unsigned int y = 0; y < h; y++)
        {
            for(unsigned int x = 0; x < w; x++)
            {
                newRe = 1.5 * (x - w/2)/(0.5 * zoom * w) + moveX;
                newIm = (y - h / 2) / (0.5 * zoom * h) + moveY;
                //cout <<"Z = "<<newRe<<" + "<<newIm<<"i"<<endl;
                unsigned int i;
                for(i = 0; i < numIteration; i++)
                {
                    oldRe = newRe;
                    oldIm = newIm;

                    newRe = pow(oldRe, 2) - pow(oldIm, 2) + cRe;
                    newIm = 2 * oldRe * oldIm + cIm;

                    if(pow(newRe, 2) + pow(newIm, 2) > 4)
                    {
                        break;
                    }
                }
                if(x <xRatio)
                    xPoint = -(1-((float)x/xRatio));
                else xPoint = (1-((float)x/xRatio));
                if(y < yRatio)
                    yPoint = -(1-((float)y/yRatio));
                else yPoint = (1-((float)y/yRatio));

                hsv cVal;
                cVal.h = i%256;
                cVal.s=255;
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
        if(numIteration > 200)
        {    numIteration-=5;
            cIm +=0.001;
        }
        else if(numIteration <= 200)
        {
            numIteration += 5;
            cIm -= 0.001;//0.025015;
            //cRe += 0.001;
            //cRe = -0.75;
        }
    //get the time and old time for time dependent input
//    oldTime = time;
//    time = getTicks();
//    frameTime = time - oldTime;
//    readKeys();
//    //ZOOM keys
//    if(keyDown(SDLK_KP_PLUS))  {zoom *= pow(1.001, frameTime);}
//    if(keyDown(SDLK_KP_MINUS)) {zoom /= pow(1.001, frameTime);}
//    //MOVE keys
//    if(keyDown(SDLK_DOWN))  {moveY += 0.0003 * frameTime / zoom;}
//    if(keyDown(SDLK_UP))  {moveY -= 0.0003 * frameTime / zoom;}
//    if(keyDown(SDLK_RIGHT)) {moveX += 0.0003 * frameTime / zoom;}
//    if(keyDown(SDLK_LEFT))  {moveX -= 0.0003 * frameTime / zoom;}
//    //CHANGE SHAPE keys
//    if(keyDown(SDLK_KP2)) {cIm += 0.0002 * frameTime / zoom;}
//    if(keyDown(SDLK_KP8)) {cIm -= 0.0002 * frameTime / zoom;}
//    if(keyDown(SDLK_KP6)) {cRe += 0.0002 * frameTime / zoom;}
//    if(keyDown(SDLK_KP4)) {cRe -= 0.0002 * frameTime / zoom;}
//    //keys to change number of iterations
//    if(keyPressed(SDLK_KP_MULTIPLY)) {maxIterations *= 2;}
//    if(keyPressed(SDLK_KP_DIVIDE))   {if(maxIterations > 2) maxIterations /= 2;}
//    //key to change the text options
//    if(keyPressed(SDLK_F1)) {showText++; showText %= 3;}
        jDisplay->swapBuffer();
    }
}

void Julia::Draw3DjuliaSet()
{
    //
}

