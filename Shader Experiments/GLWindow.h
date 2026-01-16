#include <SDL.h>

class GLWindow {
public:
    GLWindow(const char* title, int width, int height);
    ~GLWindow();

    SDL_Window* GetWindow() const { return window; }
    SDL_GLContext GetContext() const { return context; }

    void SwapBuffers() const;
    void SetVSync(bool enabled) const;

private:
    SDL_Window* window = nullptr;
    SDL_GLContext context = nullptr;
};
