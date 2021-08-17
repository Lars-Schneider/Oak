#pragma once
#include <src/Types.h>
#include <src/Renderer/OpenGLRenderer.h>
namespace Oak
{
	class Editor
	{
	public:
		Editor();
		~Editor();

		void Update(f64 ts);
	private:
		OpenGLRenderer* renderer;
	};
}