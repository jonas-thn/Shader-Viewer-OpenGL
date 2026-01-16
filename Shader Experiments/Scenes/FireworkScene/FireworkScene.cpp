#include "FireworkScene.h"
#include "../../Application.h" 

FireworkScene::FireworkScene() : 
    fireworkShader("./Shader/Firework/fireworkShader.vert", "./Shader/Firework/fireworkShader.frag"),
    screen(std::vector<float>(std::begin(screenVertices), std::end(screenVertices)),{})
{
    meshList.push_back(&screen);
}

void FireworkScene::Update(float dt) {}

void FireworkScene::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& camPos, float time)
{
    for (int i = 0; i < meshList.size(); i++)
    {
        meshList[i]->Draw(fireworkShader, view, projection, camPos, time, i, 0);
    }
}

void FireworkScene::OnActivate(ICameraControl* cameraControl)
{
    cameraControl->SetCameraConfig(2.5f, 1.0f, 0.0f);
}

void FireworkScene::OnGuiRender()
{
    ImGui::BulletText("Particles");
    ImGui::BulletText("Glow");
}