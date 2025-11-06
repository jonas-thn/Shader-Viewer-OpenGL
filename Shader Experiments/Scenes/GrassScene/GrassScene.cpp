#include "GrassScene.h"

void GrassScene::Init()
{
	standardShader.Init();
	grassShader.Init();

	plane.Init();
	plane.Translate(glm::vec3(0.0, -1.0, 0.0));
	plane.Rotate(90.0f, glm::vec3(1.0, 0.0, 0.0));
	plane.SetScale(glm::vec3(4.0));

	grass.Init();
	for (int i = 0; i < count; i++)
	{
		offsets.push_back(glm::vec3(0.0f + i, 0.0f, 0.0f));
	}
}

void GrassScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
	plane.Draw(standardShader, view, projection, camPos, time, 0);

	grass.Draw(grassShader, view, projection, camPos, time, offsets, count);
}

