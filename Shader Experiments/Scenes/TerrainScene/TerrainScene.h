#pragma once

#include "../Scene.h"
#include "../../MeshData.h"
#include <vector>

class Application;

class TerrainScene : public Scene
{
public:
    TerrainScene() = default;
    virtual ~TerrainScene() = default;

    void Init() override;
    void Update(float dt) override;
    void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time) override;

    std::string GetName() const override { return "Terrain"; }
    void OnActivate(ICameraControl* cameraControl) override;
    void OnGuiRender() override;

private:
    Shader terrainShader = Shader("./Shader/Terrain/terrainShader.vert", "./Shader/Terrain/terrainShader.frag");

    Mesh screen = Mesh(
        std::vector<float>(std::begin(screenVertices), std::end(screenVertices)),
        {}
    );
};