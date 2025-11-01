#include "LightingScene.h"

void LightingScene::Init()
{
	lightingShader.Init();

	monkey.Init();
	meshList.push_back(&monkey);

	sphere.Init();
	sphere.Translate(glm::vec3(2.0f, 0.0f, 0.0f));
	meshList.push_back(&sphere);

	pyramid.Init();
	pyramid.Translate(glm::vec3(-2.0f, 0.0f, 0.0f));
	meshList.push_back(&pyramid);

	cube.Init();
	cube.Translate(glm::vec3(0.0f, 0.0f, -2.0f));
	meshList.push_back(&cube);

	ring.Init();
	ring.Translate(glm::vec3(0.0f, 0.0f, 2.0f));
	meshList.push_back(&ring);
}

void LightingScene::Update(float dt)
{
	//...
}

void LightingScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos)
{
	for (Mesh* mesh : meshList)
	{
		mesh->Draw(lightingShader, view, projection, camPos);
	}
}
