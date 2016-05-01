#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <iostream>
#include <string>

using namespace std;

class Display
{
public:
    Display(int height, int width, const string& title);

    void swapBuffer();

    bool IsClosed();

    void getWindowSize(unsigned int *w, unsigned int *h);

    virtual ~Display();
private:
    SDL_Window *m_window;
    SDL_GLContext m_glcontext;
    bool m_isClosed;
};

#endif // DISPLAY_H
