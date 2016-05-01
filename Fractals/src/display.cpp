#include "display.h"

Display::Display(int height, int width, const string& title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    m_glcontext = SDL_GL_CreateContext(m_window);

    GLenum status = glewInit();

    if(status != GLEW_OK)
    {
        cerr<<"Glew failed to initialize"<<endl;
    }

    m_isClosed = false;
}

Display::~Display()
{
    SDL_GL_DeleteContext(m_glcontext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::getWindowSize(unsigned int *w, unsigned int *h)
{
    SDL_GL_GetDrawableSize(m_window, (int*)w, (int*)h);
}

void Display::swapBuffer()
{
    SDL_GL_SwapWindow(m_window);

    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
            m_isClosed = true;
    }
}

bool Display::IsClosed()
{
    return m_isClosed;
}
