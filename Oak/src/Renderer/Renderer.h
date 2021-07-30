#pragma once
#include <src/Types.h>
namespace Oak
{
	class Renderer
	{
	public:
		virtual ~Renderer()
		{

		}
		virtual bool Init()
		{
			return false;
		}
		virtual void BeginFrame()
		{

		}
		virtual void EndFrame()
		{

		}
		virtual void DrawQuad(f32 x, f32 y, f32 w, f32 h, i32 r, i32 g, i32 b, i32 a)
		{

		}
	private:
	};
}