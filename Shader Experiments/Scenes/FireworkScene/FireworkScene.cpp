#include "FireworkScene.h"
#include "../../Application.h" 

void FireworkScene::Init()
{
    fireworkShader.Init();

    screen.Init();
    meshList.push_back(&screen);
}

void FireworkScene::Update(float dt) {}

void FireworkScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
    for (int i = 0; i < meshList.size(); i++)
    {
        meshList[i]->Draw(fireworkShader, view, projection, camPos, time, i, 0);
    }
}

void FireworkScene::OnActivate(Application* app)
{
    app->SetCameraConfig(2.5f, 1.0f, 0.0f);
}

void FireworkScene::OnGuiRender()
{
    ImGui::BulletText("Particles");
    ImGui::BulletText("Glow");
}