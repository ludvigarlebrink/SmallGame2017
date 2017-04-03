#include "MemoryManager.h"
#include "VideoManager.h"
#include "PlayerController.h" //Used for testing, will be replace by a manager

#include "String.h"
#include "Vector.h"


#include <iostream>


MemoryManager	g_memoryManager;
VideoManager	g_videoManager;
PlayerController g_playerController;


void BigInit();
void Terminate();


int main(int argc, char *argv[])
{
	if (false);
	BigInit();

	
	while (true)
	{
		// TESTING
		g_playerController.Update();

	}
	
	Terminate();


	return 0;
}

void BigInit()
{
	g_memoryManager.StartUp();	
	g_videoManager.StartUp();
	g_playerController.StartUp();
}

void Terminate()
{
	g_videoManager.ShutDown();
	g_memoryManager.ShutDown();
}