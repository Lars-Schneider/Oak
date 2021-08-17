#include "Editor.h"

namespace Oak
{
	Editor::Editor()
	{
		renderer = new OpenGLRenderer();
	}

	Editor::~Editor()
	{
		delete renderer;
	}

	void Editor::Update(f64 timestep)
	{
		//Input

		//Update

		//Render
		renderer->BeginFrame();

		renderer->EndFrame();
	}
}