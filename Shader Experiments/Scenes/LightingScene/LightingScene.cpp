#include "LightingScene.h"
#include "../../Application.h" 

LightingScene::LightingScene() : 
    lightingShader("./Shader/Lighting/lightingShader.vert", "./Shader/Lighting/lightingShader.frag"),
    pyramid("./Models/pyramid.obj"),
    sphere("./Models/sphere.obj"),
    cone("./Models/cone.obj"),
    cube("./Models/cube.obj"),
    ring("./Models/ring.obj")
{
    cone.Translate(glm::vec3(0.0f, conePos, 0.0f));
    meshList.push_back(&cone);

    sphere.Translate(glm::vec3(0.0f, spherePos, 0.0f));
    meshList.push_back(&sphere);

    pyramid.Translate(glm::vec3(0.0f, pyramidPos, 0.0f));
    meshList.push_back(&pyramid);

    cube.Translate(glm::vec3(0.0f, cubePos, 0.0f));
    meshList.push_back(&cube);

    ring.Translate(glm::vec3(0.0f, ringPos, 0.0f));
    meshList.push_back(&ring);
}

void LightingScene::Update(float dt)
{
    MoveMesh(conePos, cone, dt);
    MoveMesh(spherePos, sphere, dt);
    MoveMesh(pyramidPos, pyramid, dt);
    MoveMesh(cubePos, cube, dt);
    MoveMesh(ringPos, ring, dt);
}

void LightingScene::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& camPos, float time)
{
    for (int i = 0; i < meshList.size(); i++)
    {
        meshList[i]->Draw(lightingShader, view, projection, camPos, time, i, 0);
    }
}

void LightingScene::MoveMesh(float& pos, Mesh& mesh, float dt)
{
    if (pos < lowerBound)
    {
        pos = upperBound;
    }

    pos -= speed * dt;

    mesh.SetPos(glm::vec3(0.0f, pos, 0.0f));
}

void LightingScene::OnActivate(ICameraControl* cameraControl)
{
    cameraControl->SetCameraConfig(7.0f, 1.0f, 1.75f);
}

void LightingScene::OnGuiRender()
{
    ImGui::BulletText("Ambient");
    ImGui::BulletText("Hemispheric");
    ImGui::BulletText("Diffuse");
    ImGui::BulletText("Specular");
    ImGui::BulletText("Fresnel");
}