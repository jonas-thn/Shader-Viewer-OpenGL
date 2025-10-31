#pragma once

#include <gl/glew.h>

#include <SDL.h>

#include "MeshData.h"
#include "Shader.h"
#include "Mesh.h"

class Application
{
public:
	void Init();
	void Setup();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

private:


public:
	bool running = true;

private:
	SDL_Window* window;
	SDL_GLContext glContext;

	int width = 800;
	int height = 600;

	float lastFrame;

	unsigned int VBO;
	unsigned int VAO;

	Shader standardShader = Shader("Shader/Standard/standardShader.vert", "Shader/Standard/standardShader.frag");

	Mesh quad = Mesh(
		std::vector<float>(std::begin(quadVertices), std::end(quadVertices)),
		std::vector<unsigned int>(std::begin(quadIndices), std::end(quadIndices))
	);

	Mesh triangle = Mesh("./Models/triangle.obj");
};

