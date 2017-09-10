
#include "Core.h"
#include "Gfx.h"

#include "RenderingSystem.h"

using namespace ebola;

int main(char argc, char* argv[])
{
	gfx::RenderingSystem renderer;
	renderer.Initialize();
	renderer.Shutdown();

	return 0;
}