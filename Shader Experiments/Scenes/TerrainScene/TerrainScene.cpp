#include "TerrainScene.h"
#include "../../Application.h"

TerrainScene::TerrainScene() :
    terrainShader("./Shader/Terrain/terrainShader.vert", "./Shader/Terrain/terrainShader.frag"),
    screen(std::vector<float>(std::begin(screenVertices), std::end(screenVertices)),{})
{
    meshList.push_back(&screen);
}

void TerrainScene::Update(float dt) {}

void TerrainScene::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& camPos, float time)
{
    for (int i = 0; i < meshList.size(); i++)
    {
        meshList[i]->Draw(terrainShader, view, projection, camPos, time, i, 0);
    }
}

void TerrainScene::OnActivate(ICameraControl* cameraControl)
{
    cameraControl->SetCameraConfig(2.5f, 1.0f, 0.0f);
}

void TerrainScene::OnGuiRender()
{
    ImGui::BulletText("Procedual Generation");
    ImGui::BulletText("Atmosphere");
}