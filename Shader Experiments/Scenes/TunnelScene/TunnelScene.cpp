#include "TunnelScene.h"

void TunnelScene::Init()
{
	glassShder.Init();

	screen.Init();
	meshList.push_back(&screen);
}

void TunnelScene::Update(float dt)
{
	//...
}

void TunnelScene::Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time)
{
	for (int i = 0; i < meshList.size(); i++)
	{
		meshList[i]->Draw(glassShder, view, projection, camPos, time, i, 0);
	}
}