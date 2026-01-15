#include "GLWindow.h"
#include <stdexcept>

void GLWindow::SwapBuffers() const
{
    SDL_GL_SwapWindow(m_window);
}

void GLWindow::SetVSync(bool enabled) const
{
    if (SDL_GL_SetSwapInterval(enabled ? 1 : 0) != 0)
    {
        fprintf(stderr, "VSync not supported");
    }
}
