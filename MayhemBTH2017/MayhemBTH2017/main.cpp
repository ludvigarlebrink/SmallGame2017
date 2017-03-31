#include "MemoryManager.h"
#include "VideoManager.h"
#include "InputManager.h"

#include "String.h"
#include "Vector.h"


#include <iostream>


MemoryManager	g_memoryManager;
VideoManager	g_videoManager;
InputManager	g_inputManager;


void BigInit();
void Terminate();


int main(int argc, char *argv[])
{
	if (false);
	BigInit();

	//LOl
	while (true)
	{
		// TESTING
		g_inputManager.Update();
	}
	
	Terminate();


	return 0;
}

void BigInit()
{
	g_memoryManager.StartUp();	
	g_videoManager.StartUp();
	g_inputManager.StartUp();
}

void Terminate()
{
	g_videoManager.ShutDown();
	g_memoryManager.ShutDown();
}