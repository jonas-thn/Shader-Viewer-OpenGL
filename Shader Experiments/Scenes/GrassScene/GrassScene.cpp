#include "GrassScene.h"
#include "../../Application.h"

GrassScene::GrassScene() : 
    standardShader("./Shader/Standard/standardShader.vert", "./Shader/Standard/standardShader.frag"),
    grassShader("./Shader/Grass/grassShader.vert", "./Shader/Grass/grassShader.frag"),

    plane("./Models/quad.obj"),
    sphere("./Models/sphere.obj"),

    grass1("./Models/grass.obj"),
    grass2("./Models/grass.obj")
{
    plane.Translate(glm::vec3(0.0, -0.5, 0.0));
    plane.Rotate(90.0f, glm::vec3(1.0, 0.0, 0.0));
    plane.SetScale(glm::vec3(4.0));

    sphere.Translate(glm::vec3(1.0, 2.0, -2.0));
    sphere.SetScale(glm::vec3(0.5));

     meshList.push_back(&plane);
     meshList.push_back(&sphere);
}

void GrassScene::Update(float dt) {}

void GrassScene::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& camPos, float time)
{
    plane.Draw(standardShader, view, projection, camPos, time, 800, 0);

    grass1.Draw(grassShader, view, projection, camPos, time, 0, count);
    grass2.Draw(grassShader, view, projection, camPos, time, 1, count);
}

void GrassScene::OnActivate(ICameraControl* cameraControl)
{
    cameraControl->SetCameraConfig(7.0f, 0.3f, 2.0f);
}

void GrassScene::OnGuiRender()
{
    ImGui::BulletText("Instancing");
    ImGui::BulletText("Wind Bending");
}