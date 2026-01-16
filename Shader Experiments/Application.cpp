#include "Application.h"

#include "ImGui/imgui_impl_sdl2.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "Scenes/Scene.h"

#include "Scenes/LightingScene/LightingScene.h"
#include "Scenes/EmptyScene/EmptyScene.h"
#include "Scenes/OtherScene/OtherScene.h"
#include "Scenes/PlanetScene/PlanetScene.h"
#include "Scenes/RaymarchingScene/RaymarchingScene.h"
#include "Scenes/TerrainScene/TerrainScene.h"
#include "Scenes/GrassScene/GrassScene.h"
#include "Scenes/FireworkScene/FireworkScene.h"
#include "Scenes/WaterScene/WaterScene.h"
#include "Scenes/TunnelScene/TunnelScene.h"

void Application::Init()
{
    try 
    {
        window = std::make_unique<GLWindow>("OpenGL Shader Editor", width, height);

        window->SetVSync(true);
    }
    catch (const std::exception& e) 
    {
        fprintf(stderr, "Init failed: %s\n", e.what());
        running = false;
        return;
    }

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        fprintf(stderr, "GLEW Init Error: %s\n", glewGetErrorString(err));
        running = false;
        return;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplSDL2_InitForOpenGL(window->GetWindow(), window->GetContext());
    ImGui_ImplOpenGL3_Init("#version 130");

    InitImGuiStyle();

    glEnable(GL_DEPTH_TEST);
    uiWidth = static_cast<int>(width * uiWidthPercent);
    glViewport(-uiWidth, 0, width + uiWidth, height);
}

void Application::Setup()
{
    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    view = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    sceneList.push_back(std::make_shared<EmptyScene>());
    sceneList.push_back(std::make_shared<LightingScene>());
    sceneList.push_back(std::make_shared<WaterScene>());
    sceneList.push_back(std::make_shared<RaymarchingScene>());
    sceneList.push_back(std::make_shared<GrassScene>());
    sceneList.push_back(std::make_shared<FireworkScene>());
    sceneList.push_back(std::make_shared<TunnelScene>());
    sceneList.push_back(std::make_shared<PlanetScene>());
    sceneList.push_back(std::make_shared<TerrainScene>());
    sceneList.push_back(std::make_shared<OtherScene>());

    for (auto& scene : sceneList)
    {
        scene->Init();
    }

    if (!sceneList.empty())
    {
        activeScene = sceneList[0].get();
        activeScene->OnActivate(this);
    }
}

void Application::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
        {
            running = false;
        }

        if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                width = event.window.data1;
                height = event.window.data2;
                projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
                uiWidth = static_cast<int>(width * uiWidthPercent);
                glViewport(-uiWidth, 0, width + uiWidth, height);
            }
        }
    }
}

void Application::Update()
{
    float currentFrame = static_cast<float>(SDL_GetTicks());
    float deltaTime = (currentFrame - lastFrame) / 1000.0f;
    lastFrame = currentFrame;

    uiWidth = static_cast<int>(width * uiWidthPercent);

    static float angle = 0.0f;
    angle -= camSpeed * deltaTime;

    camPos.x = sin(angle) * camRadius;
    camPos.y = cameraHeight;
    camPos.z = cos(angle) * camRadius;

    view = glm::lookAt(camPos,
        glm::vec3(0.0, 0.0, 0.0), 
        glm::vec3(0.0f, 1.0f, 0.0f) 
    );

    if (activeScene)
    {
        activeScene->Update(deltaTime);
    }
}

void Application::Render()
{
    glViewport(-uiWidth, 0, width + uiWidth, height);

    DrawGUI();
    DrawScene();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    window->SwapBuffers();
}

void Application::DrawGUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2((float)(width - uiWidth), 0.0f));
    ImGui::SetNextWindowSize(ImVec2((float)uiWidth, (float)height));

    ImGui::Begin("Shader Scenes", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

    const int buttonHeight = 20;

    for (const auto& scene : sceneList)
    {
        ImGui::SeparatorText(scene->GetName().c_str());

        std::string btnLabel = "Load Scene##" + scene->GetName();

        if (ImGui::Button(btnLabel.c_str(), ImVec2(-1, buttonHeight)))
        {
            activeScene = scene.get();
            activeScene->OnActivate(this);
        }

        if (activeScene == scene.get())
        {
            std::string infoText = scene->GetName() + " Shader:";
            ImGui::Text("%s", infoText.c_str());

            scene->OnGuiRender();
        }

        ImGui::Dummy(ImVec2(0.0, 10.0));
    }

    ImGui::End();
    ImGui::Render();
}

void Application::DrawScene()
{
    glClearColor(0.1f, 0.1f, 0.105f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (activeScene)
    {
        activeScene->Draw(view, projection, camPos, (SDL_GetTicks() * 0.001f));
    }
}

void Application::SetCameraConfig(float radius, float speed, float height)
{
    this->camRadius = radius;
    this->camSpeed = speed;
    this->cameraHeight = height;
}

void Application::InitImGuiStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::StyleColorsDark();

    ImVec4 blackColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    ImVec4 grey02Color = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
    ImVec4 grey04Color = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
    ImVec4 grey06Color = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);
    ImVec4 grey08Color = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
    ImVec4 whiteColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    style.Colors[ImGuiCol_FrameBg] = grey02Color;
    style.Colors[ImGuiCol_FrameBgHovered] = grey04Color;
    style.Colors[ImGuiCol_FrameBgActive] = grey06Color;
    style.Colors[ImGuiCol_PopupBg] = grey02Color;
    style.Colors[ImGuiCol_Border] = grey04Color;
    style.Colors[ImGuiCol_BorderShadow] = blackColor;
    style.Colors[ImGuiCol_Header] = grey04Color;
    style.Colors[ImGuiCol_HeaderHovered] = grey06Color;
    style.Colors[ImGuiCol_HeaderActive] = grey08Color;
    style.Colors[ImGuiCol_Text] = whiteColor;
    style.Colors[ImGuiCol_CheckMark] = whiteColor;
    style.Colors[ImGuiCol_ScrollbarBg] = grey02Color;
    style.Colors[ImGuiCol_ScrollbarGrab] = grey04Color;
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = grey06Color;
    style.Colors[ImGuiCol_ScrollbarGrabActive] = grey08Color;
    style.Colors[ImGuiCol_Button] = grey04Color;
    style.Colors[ImGuiCol_SliderGrab] = grey08Color;
    style.Colors[ImGuiCol_SliderGrabActive] = whiteColor;
    style.Colors[ImGuiCol_ButtonHovered] = grey06Color;
    style.Colors[ImGuiCol_ButtonActive] = grey08Color;
    style.Colors[ImGuiCol_TextSelectedBg] = grey06Color;
    style.Colors[ImGuiCol_Separator] = grey04Color;
    style.Colors[ImGuiCol_SeparatorHovered] = grey06Color;
    style.Colors[ImGuiCol_SeparatorActive] = grey08Color;
    style.Colors[ImGuiCol_TitleBg] = grey02Color;
    style.Colors[ImGuiCol_TitleBgActive] = grey04Color;
    style.Colors[ImGuiCol_TitleBgCollapsed] = grey02Color;
    style.Colors[ImGuiCol_ResizeGrip] = grey04Color;
    style.Colors[ImGuiCol_ResizeGripHovered] = grey06Color;
    style.Colors[ImGuiCol_ResizeGripActive] = grey08Color;
    style.Colors[ImGuiCol_DragDropTarget] = grey08Color;
    style.Colors[ImGuiCol_NavHighlight] = grey06Color;
    style.Colors[ImGuiCol_NavWindowingHighlight] = grey06Color;
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0, 0, 0, 0.4f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0, 0, 0, 0.4f);
    style.WindowPadding = ImVec2(20.0f, 20.0f);
}

Application::~Application() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
