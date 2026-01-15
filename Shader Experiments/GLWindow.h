#include <SDL.h>

class GLWindow {
public:
    GLWindow(const char* title, int width, int height);
    ~GLWindow();

    SDL_Window* window() const { return m_window; }
    SDL_GLContext context() const { return m_context; }

    void SwapBuffers() const;
    void SetVSync(bool enabled) const;

private:
    SDL_Window* m_window = nullptr;
    SDL_GLContext m_context = nullptr;
};
