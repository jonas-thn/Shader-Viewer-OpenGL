#include "TunnelScene.h"
#include "../../Application.h" 

TunnelScene::TunnelScene() : 
    tunnelShder("./Shader/Tunnel/tunnelShader.vert", "./Shader/Tunnel/tunnelShader.frag"),
    screen(std::vector<float>(std::begin(screenVertices), std::end(screenVertices)),{})
{
    meshList.push_back(&screen);
}

void TunnelScene::Update(float dt) {}

void TunnelScene::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& camPos, float time)
{
    for (int i = 0; i < meshList.size(); i++)
    {
        meshList[i]->Draw(tunnelShder, view, projection, camPos, time, i, 0);
    }
}

void TunnelScene::OnActivate(ICameraControl* cameraControl)
{
    cameraControl->SetCameraConfig(2.5f, 1.0f, 0.0f);
}

void TunnelScene::OnGuiRender() {}