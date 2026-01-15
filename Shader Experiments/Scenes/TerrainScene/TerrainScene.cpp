#include "TerrainScene.h"
#include "../../Application.h"

void TerrainScene::Init()
{
    terrainShader.Init();

    screen.Init();
    meshList.push_back(&screen);
}

void TerrainScene::Update(float dt) {}

void TerrainScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
    for (int i = 0; i < meshList.size(); i++)
    {
        meshList[i]->Draw(terrainShader, view, projection, camPos, time, i, 0);
    }
}

void TerrainScene::OnActivate(Application* app)
{
    app->SetCameraConfig(2.5f, 1.0f, 0.0f);
}

void TerrainScene::OnGuiRender()
{
    ImGui::BulletText("Procedual Generation");
    ImGui::BulletText("Atmosphere");
}