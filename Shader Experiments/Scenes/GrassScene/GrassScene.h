#pragma once

#include "../../MeshData.h"
#include <vector>
#include "../../Shader.h"
#include "../../Mesh.h"
#include "../../MeshInstances.h"

class GrassScene
{
public:
	GrassScene() = default;

	void Init();
	void Draw(glm::mat4& view, glm::mat4& projection, glm::vec3& camPos, float time);

private:
	Shader standardShader = Shader("./Shader/Standard/standardShader.vert", "./Shader/Standard/standardShader.frag");
	Shader grassShader = Shader("./Shader/Grass/grassShader.vert", "./Shader/Grass/grassShader.frag");

	Mesh plane = Mesh("./Models/quad.obj");
	MeshInstances grass = MeshInstances("./Models/grass.obj");

	std::vector<glm::vec3> offsets;
	int count = 5;
};

