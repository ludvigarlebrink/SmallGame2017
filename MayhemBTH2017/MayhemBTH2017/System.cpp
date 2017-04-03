#include "System.h"


#include "LevelEditor.h"



System::System()
{
	Init();
}


System::~System()
{
}

//::.. THE MAIN LOOP ..:://
void System::Run()
{
	glDisable(GL_CULL_FACE);
	LevelEditor l;


	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		l.Update();
		// Switch between back and front buffer.
		m_videoManager->Swap();
	}
}

void System::Init()
{
	m_videoManager = VideoManager::Get();
}
