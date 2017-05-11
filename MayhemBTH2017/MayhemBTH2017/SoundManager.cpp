#include "SoundManager.h"


SoundManager * SoundManager::m_instance = nullptr;

SoundManager::SoundManager()
{
	// Do nothing...
}


SoundManager::~SoundManager()
{
	// Do nothing...
}

void SoundManager::StartUp()
{
	if (m_instance == nullptr)
	{
		m_instance = this;
		Init();
	}
}

void SoundManager::ShutDown()
{
	m_system->release();
}

SoundManager * SoundManager::Get()
{
	return m_instance;
}

bool SoundManager::GetPlaying()
{
	return m_playing;
}
float SoundManager::GetVolume()
{
	return m_volume;
}

void SoundManager::SetPause(SoundType channel, bool pause)
{
	m_channelGroup[channel]->setPaused(pause);
}

void SoundManager::SetVolume(SoundType channel, float volume)
{
	m_channelGroup[channel]->setVolume(volume);
}

void SoundManager::Play(SoundType channel, Music sound)
{
	m_system->playSound(m_musicSound[sound], m_channelGroup[channel], false, &m_channel[channel]);
}

void SoundManager::Play(SoundType channel, SFX sound)
{
	m_system->playSound(m_sfxSound[sound], m_channelGroup[channel], false, &m_channel[channel]);
}

void SoundManager::Update()
{
	m_system->update();
}


void SoundManager::Init()
{

	if (FMOD::System_Create(&m_system) != FMOD_OK)
	{
		std::cout << "FMOD System_Create Error!" << std::endl;
		return;
	}

	int driverCount = 0;
	m_system->getNumDrivers(&driverCount);

	if (driverCount == 0)
	{
		std::cout << "FMOD driverCount Error!" << std::endl;
		return;
	}

	m_system->init(36, FMOD_INIT_NORMAL, NULL);

	for (int i = 0; i < NUM_SOUNDTYPE; i++)
		m_system->createChannelGroup(NULL, &m_channelGroup[i]);

	InitMusic();
	InitNoneLooping();

}

void SoundManager::InitMusic()
{
	std::string path = ".\\Assets\\Sounds\\Music\\";
	std::string soundPath;
	int counter = 0;

	for (auto & p : std::experimental::filesystem::directory_iterator(path))
	{
		soundPath = p.path().string();
		m_system->createStream(soundPath.c_str(), FMOD_DEFAULT, 0, &m_musicSound[counter]);
		m_system->playSound(m_musicSound[counter], m_channelGroup[SOUND_CHANNEL_MUSIC], true, &m_channel[SOUND_CHANNEL_MUSIC]);
		m_channel[SOUND_CHANNEL_MUSIC]->setChannelGroup(m_channelGroup[SOUND_CHANNEL_MUSIC]);

		if (counter < NUM_MUSIC)
			counter++;
	}

}

void SoundManager::InitNoneLooping()
{
	std::string path = ".\\Assets\\Sounds\\SFX\\";
	std::string soundPath;
	int counter = 0;

	for (auto & p : std::experimental::filesystem::directory_iterator(path))
	{
		soundPath = p.path().string();
		std::cout << soundPath.c_str() << std::endl;
		m_system->createSound(soundPath.c_str(), FMOD_LOOP_OFF, 0, &m_sfxSound[counter]);
		m_system->playSound(m_sfxSound[counter], m_channelGroup[SOUND_CHANNEL_NONE_LOOPING], true, &m_channel[SOUND_CHANNEL_NONE_LOOPING]);
		m_channel[SOUND_CHANNEL_NONE_LOOPING]->setChannelGroup(m_channelGroup[SOUND_CHANNEL_NONE_LOOPING]);

		if (counter < NUM_SFX)
			counter++;
	}

}
