#include "Application.h"

int main(int argc, char** argv)
{
	Application app;

	app.Init();
	app.Setup();

	while (app.running)
	{
		app.ProcessInput();
		app.Update();
		app.Render();
	}

	return 0;
}