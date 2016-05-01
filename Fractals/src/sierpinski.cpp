#include "sierpinski.h"

#include <iostream>


Sierpinski::Sierpinski(unsigned  int nIter)
{
    sDisplay = new Display(400,600, "Sierpinski Fractal");
    numIteration = nIter;
}

void Sierpinski::DrawSierpinskiCarpet()
{
    unsigned int h, w;
    sDisplay->getWindowSize(&w, &h);

    point A, B, C, D;
    A.x = 0.75f;
    A.y = 0.75f;
    B.x = 0.75f;
    B.y = -0.75f;
    C.x = -0.75f;
    C.y = -0.75f;
    D.x = -0.75f;
    D.y = 0.75f;

    glViewport(0,0,w,h);
    glOrtho(-1.0, 1.0,1.0,-1.0,0.0,0.0);

    while(!sDisplay->IsClosed())
    {
        glClearColor(0.2f , 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawSubSquare(1, A, B, C,D);
        sDisplay->swapBuffer();
    }
}

void Sierpinski::drawSubSquare(unsigned int n, point A, point B, point C, point D)
{
    point E, F, G, H;
//    glBegin(GL_LINE_LOOP);
//        glColor3f(1.0f,1.0f,1.0f);
//        glVertex2f(A.x, A.y);
//        glVertex2f(B.x, B.y);
//        glVertex2f(C.x, C.y);
//        glVertex2f(D.x, D.y);
//    glEnd();
//    glFlush();

    if(n < numIteration)
    {
        E.x = A.x/ 2 ;
        E.y = A.y/2;
        F.x = B.x / 2 ;
        F.y = B.y / 2;
        G.x = C.x / 2 ;
        G.y = C.y / 2;
        H.x = D.x / 2;
        H.y = D.y / 2;
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex2f(E.x, E.y);
        glVertex2f(F.x, F.y);
        glVertex2f(G.x, G.y);
        glVertex2f(H.x, H.y);
        glEnd();
        glFlush();

        drawSubSquare(n + 1, A,  B,  C,  D);
        drawSubSquare(n + 1,  A,   B,   C,   D);
        drawSubSquare(n + 1,   A,   B,   C,   D);
        drawSubSquare(n + 1,   A,   B,   C,   D);
        drawSubSquare(n + 1,   A,   B,   C,   D);
        drawSubSquare(n + 1,   A,   B,   C,   D);
        drawSubSquare(n + 1,   A,   B,   C,   D);
        drawSubSquare(n + 1,   A,   B,   C,   D);
    }
}

void Sierpinski::DrawSierpinskiTriangle()
{
    unsigned int h, w;
    sDisplay->getWindowSize(&w, &h);

    point A, B, C;
    A.x = 0.0f;
    A.y = 0.80f;
    B.x = -0.50f;
    B.y = -0.50f;
    C.x = 0.50f;
    C.y = -0.50f;

    glViewport(0,0,w,h);
    glOrtho(-1.0, 1.0,1.0,-1.0,0.0,0.0);

    while(!sDisplay->IsClosed())
    {
        glClearColor(0.2f , 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawSubTriangle(1, A, B, C);
        sDisplay->swapBuffer();
    }
}

void Sierpinski::drawSubTriangle(unsigned int n, point A, point B, point C)
{
    point D, E, F;
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(A.x, A.y);
    glVertex2f(B.x, B.y);
    glVertex2f(C.x, C.y);
    glEnd();
    glFlush();
    if(n < numIteration)
    {
        D.x = (A.x + B.x) / 2 ;
        D.y = (A.y + B.y) / 2 ;
        E.x = (A.x + C.x) / 2 ;
        E.y = (A.y + C.y) / 2 ;
        F.x = (B.x + C.x) / 2 ;
        F.y = (B.y + C.y) / 2 ;

        drawSubTriangle(n+1, D, A, E);
        drawSubTriangle(n+1, D, B, F);
        drawSubTriangle(n+1, F, E, C);

//
//        cout<<"A = ("<<D.x<<" "<<D.y<<")"<<endl;
//        glBegin(GL_LINE_LOOP);
//        glColor3f(1.0f,1.0f,1.0f);
//        glVertex2f(F.x, F.y);
//        glVertex2f(E.x, E.y);
//        glVertex2f(C.x, C.y);
//    glEnd();
//    glFlush();
    }
}
Sierpinski::~Sierpinski()
{
    delete sDisplay;
}
