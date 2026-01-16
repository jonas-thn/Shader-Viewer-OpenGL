#include "PlanetScene.h"
#include "../../Application.h" 

PlanetScene::PlanetScene() :
    planetShader("./Shader/Planet/planetShader.vert", "./Shader/Planet/planetShader.frag"),
    screen(std::vector<float>(std::begin(screenVertices), std::end(screenVertices)), {})
{
    meshList.push_back(&screen);
}

void PlanetScene::Update(float dt) {}

void PlanetScene::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& camPos, float time)
{
    for (int i = 0; i < meshList.size(); i++)
    {
        meshList[i]->Draw(planetShader, view, projection, camPos, time, i, 0);
    }
}

void PlanetScene::OnActivate(ICameraControl* cameraControl)
{
    cameraControl->SetCameraConfig(2.5f, 1.0f, 0.0f);
}

void PlanetScene::OnGuiRender()
{
    ImGui::BulletText("Signed Distance Fields");
    ImGui::BulletText("Noise");
    ImGui::BulletText("3D Mapping");
}