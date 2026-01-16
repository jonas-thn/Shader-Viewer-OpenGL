#include "WaterScene.h"
#include "../../Application.h"
void WaterScene::Init()
{
    waterShader.Init();

    screen.Init();
    meshList.push_back(&screen);
}

void WaterScene::Update(float dt) {}

void WaterScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
    for (int i = 0; i < meshList.size(); i++)
    {
        meshList[i]->Draw(waterShader, view, projection, camPos, time, i, 0);
    }
}

void WaterScene::OnActivate(ICameraControl* cameraControl)
{
    cameraControl->SetCameraConfig(2.5f, 1.0f, 0.0f);
}

void WaterScene::OnGuiRender()
{
    ImGui::BulletText("Fractal Brownian Motion");
    ImGui::BulletText("Sun Reflection");
    ImGui::BulletText("Pseudo-Subsurface-Scattering");
}