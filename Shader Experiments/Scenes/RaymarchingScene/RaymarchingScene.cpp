#include "RaymarchingScene.h"
#include "../../Application.h" 

RaymarchingScene::RaymarchingScene() :
    raymarchShader("./Shader/Raymarching/raymarchShader.vert", "./Shader/Raymarching/raymarchShader.frag"),
    screen(std::vector<float>(std::begin(screenVertices), std::end(screenVertices)),{})
{
    meshList.push_back(&screen);
}

void RaymarchingScene::Update(float dt) {}

void RaymarchingScene::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& camPos, float time)
{
    for (int i = 0; i < meshList.size(); i++)
    {
        meshList[i]->Draw(raymarchShader, view, projection, camPos, time, i, 0);
    }
}

void RaymarchingScene::OnActivate(ICameraControl* cameraControl)
{
    cameraControl->SetCameraConfig(2.5f, 1.0f, 0.0f);
}

void RaymarchingScene::OnGuiRender()
{
    ImGui::BulletText("Smooth Blending");
    ImGui::BulletText("Distance Fog");
    ImGui::BulletText("Soft Shadows");
    ImGui::BulletText("Ambient Occlusion");
}