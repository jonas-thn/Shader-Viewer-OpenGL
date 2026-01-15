#include "RaymarchingScene.h"
#include "../../Application.h" 

void RaymarchingScene::Init()
{
    raymarchShader.Init();

    screen.Init();
    meshList.push_back(&screen);
}

void RaymarchingScene::Update(float dt) {}

void RaymarchingScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
    for (int i = 0; i < meshList.size(); i++)
    {
        meshList[i]->Draw(raymarchShader, view, projection, camPos, time, i, 0);
    }
}

void RaymarchingScene::OnActivate(Application* app)
{
    app->SetCameraConfig(2.5f, 1.0f, 0.0f);
}

void RaymarchingScene::OnGuiRender()
{
    ImGui::BulletText("Smooth Blending");
    ImGui::BulletText("Distance Fog");
    ImGui::BulletText("Soft Shadows");
    ImGui::BulletText("Ambient Occlusion");
}