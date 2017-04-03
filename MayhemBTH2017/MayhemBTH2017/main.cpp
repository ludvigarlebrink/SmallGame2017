#include "MemoryManager.h"
#include "ResourceManager.h"
#include "VideoManager.h"

#include "LevelEditor.h" //Used for debugging

#include "System.h"


// Global singleton managers.
MemoryManager	g_memoryManager;
ResourceManager	g_resourceManager;
VideoManager	g_videoManager;
LevelEditor		g_levelEditor; //Used for debugging


void BigInit();
void Terminate();


int main(int argc, char *argv[])
{
	// Init all singleton managers.
	BigInit();

	// Create the main system.
	System system;

	// Start the main loop.
	//system.Run();

	g_levelEditor.Update();
	

	// Terminate all singleton managers in
	// reverse order from creation.
	Terminate();
	getchar();
	return 0;
}

void BigInit()
{
	g_memoryManager.StartUp();		// 1.
	g_resourceManager.StartUp();	// 2.
	g_videoManager.StartUp();		// 3.
}

void Terminate()
{
	g_videoManager.ShutDown();		// 3.
	g_resourceManager.ShutDown();	// 2.
	g_memoryManager.ShutDown();		// 1.
}