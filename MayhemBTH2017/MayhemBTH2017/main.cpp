#include "MemoryManager.h"
#include "ResourceManager.h"
#include "VideoManager.h"
#include "StateManager.h"
#include "InputManager.h"

#include "System.h"


// Global singleton managers.
MemoryManager	g_memoryManager;
ResourceManager	g_resourceManager;
VideoManager	g_videoManager;
StateManager	g_stateManager;
InputManager	g_inputManager;


void BigInit();
void Terminate();


int main(int argc, char *argv[])
{
	// Init all singleton managers.
	BigInit();

	// Create the main system.
	System system;

	// Start the main loop.
	system.Run();

	// Terminate all singleton managers in
	// reverse order from creation.
	Terminate();

	return 0;
}

void BigInit()
{
	g_memoryManager.StartUp();		// 1.
	g_resourceManager.StartUp();	// 2.
	g_videoManager.StartUp();		// 3.
	g_stateManager.StartUp();		// 4.
	g_inputManager.StartUp();		// 5.
}

void Terminate()
{
	g_inputManager.ShutDown();		// 5.
	g_stateManager.ShutDown();		// 4.
	g_videoManager.ShutDown();		// 3.
	g_resourceManager.ShutDown();	// 2.
	g_memoryManager.ShutDown();		// 1.
}