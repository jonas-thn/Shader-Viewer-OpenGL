#pragma once

#include <gl/glew.h>

#include "ImGui/imgui.h"

#include <SDL.h>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//TDOD:
// GLWindow
// Camera Interface
// UI Cleanup
// getter / setter
// const correctness
// smart pointers 
// Init vs Constructor
// error handling / exceptions

class Scene;

class Application
{
public:
    ~Application();

    void Init();
    void Setup();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

    void SetCameraConfig(float radius, float speed, float height);

public:
    bool running = true;

private:
    void DrawGUI();
    void DrawScene();

    void InitImGuiStyle();

private:
    SDL_Window* window = nullptr;
    SDL_GLContext glContext;

    int width = 800;
    int height = 600;

    float lastFrame = 0.0f;

    Scene* activeScene = nullptr;

    std::vector<std::shared_ptr<Scene>> sceneList;

    glm::vec3 camPos;
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    float camRadius = 2.5f;
    float camSpeed = 1.0f;
    float cameraHeight = 0.0f;

    float uiWidthPercent = 0.35f;
    int uiWidth = 0;
};