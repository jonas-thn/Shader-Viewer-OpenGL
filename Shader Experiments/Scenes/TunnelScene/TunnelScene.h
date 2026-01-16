#pragma once

#include "../Scene.h"
#include "../../MeshData.h"
#include <vector>

class Application;

class TunnelScene : public Scene
{
public:
    TunnelScene() = default;
    virtual ~TunnelScene() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time) override;

    std::string GetName() const override { return "Tunnel"; }
    void OnActivate(ICameraControl* cameraControl) override;
    void OnGuiRender() override;

private:
    Shader tunnelShder = Shader("./Shader/Tunnel/tunnelShader.vert", "./Shader/Tunnel/tunnelShader.frag");

    Mesh screen = Mesh(
        std::vector<float>(std::begin(screenVertices), std::end(screenVertices)),
        {}
    );
};