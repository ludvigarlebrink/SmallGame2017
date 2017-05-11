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

void SoundManager::SetPause(SoundGroups channel, bool pause)
{
	m_channelGroup[channel]->setPaused(pause);
}

void SoundManager::SetVolume(SoundGroups channel, float volume)
{
	m_channelGroup[channel]->setVolume(volume);
}

void SoundManager::Play(Music sound, bool paused)
{
	bool playing;
	if (!m_channelGroup[SOUND_GROUP_MUSIC]->isPlaying(&playing))
		m_system->playSound(m_musicSound[sound], m_channelGroup[SOUND_GROUP_MUSIC], paused, &m_channel[SOUND_CHANNEL_MUSIC_01]);
	else
		m_system->playSound(m_musicSound[sound], m_channelGroup[SOUND_GROUP_MUSIC], paused, &m_channel[SOUND_CHANNEL_MUSIC_02]);
}

void SoundManager::Play(SFX sound, bool paused)
{
	bool playing;
	if (!m_channelGroup[SOUND_GROUP_NONE_LOOPING]->isPlaying(&playing))
		m_system->playSound(m_sfxSound[sound], m_channelGroup[SOUND_GROUP_NONE_LOOPING], paused, &m_channel[SOUND_CHANNEL_NONE_LOOPING_01]);
	else
		m_system->playSound(m_sfxSound[sound], m_channelGroup[SOUND_GROUP_NONE_LOOPING], paused, &m_channel[SOUND_CHANNEL_NONE_LOOPING_02]);
}

void SoundManager::Play(Ambient ambient, bool paused)
{
	bool playing;
	if (!m_channelGroup[SOUND_GROUP_AMBIENT]->isPlaying(&playing))
		m_system->playSound(m_sfxSound[ambient], m_channelGroup[SOUND_GROUP_AMBIENT], paused, &m_channel[SOUND_CHANNEL_AMBIENT_01]);
	else
		m_system->playSound(m_sfxSound[ambient], m_channelGroup[SOUND_GROUP_AMBIENT], paused, &m_channel[SOUND_CHANNEL_AMBIENT_02]);
}

void SoundManager::SwapMusic(Music newSound)
{
	unsigned long long dspClock;
	int rate;
	float volume;
	m_channelGroup[SOUND_GROUP_MUSIC]->getVolume(&volume);

	m_system->getSoftwareFormat(&rate, 0, 0);
	m_channel[SOUND_CHANNEL_MUSIC_01]->getDSPClock(0, &dspClock);
	m_channel[SOUND_CHANNEL_MUSIC_01]->addFadePoint(dspClock, volume);
	m_channel[SOUND_CHANNEL_MUSIC_01]->addFadePoint(dspClock + (rate * 3), 0.0);
	m_channel[SOUND_CHANNEL_MUSIC_01]->setDelay(0, dspClock + (rate * 3), true);

	Play(newSound);

	m_channel[SOUND_CHANNEL_MUSIC_01]->getDSPClock(0, &dspClock);
	m_channel[SOUND_CHANNEL_MUSIC_01]->addFadePoint(dspClock, 0); 
	m_channel[SOUND_CHANNEL_MUSIC_01]->addFadePoint(dspClock + (rate * 4), volume);

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
		m_system->playSound(m_musicSound[counter], m_channelGroup[SOUND_GROUP_MUSIC], true, &m_channel[SOUND_CHANNEL_MUSIC_01]);
		m_channel[SOUND_CHANNEL_MUSIC_01]->setChannelGroup(m_channelGroup[SOUND_GROUP_MUSIC]);
		m_channel[SOUND_CHANNEL_MUSIC_02]->setChannelGroup(m_channelGroup[SOUND_GROUP_MUSIC]);

		if (counter < NUM_MUSIC)
			counter++;
	}
}

void SoundManager::InitAmbient()
{
	std::string path = ".\\Assets\\Sounds\\Ambient\\";
	std::string soundPath;
	int counter = 0;

	for (auto & p : std::experimental::filesystem::directory_iterator(path))
	{
		soundPath = p.path().string();
		m_system->createSound(soundPath.c_str(), FMOD_DEFAULT, 0, &m_sfxSound[counter]);
		m_system->playSound(m_sfxSound[counter], m_channelGroup[SOUND_GROUP_AMBIENT], true, &m_channel[SOUND_CHANNEL_AMBIENT_01]);
		m_channel[SOUND_CHANNEL_AMBIENT_01]->setChannelGroup(m_channelGroup[SOUND_GROUP_AMBIENT]);
		m_channel[SOUND_CHANNEL_AMBIENT_02]->setChannelGroup(m_channelGroup[SOUND_GROUP_AMBIENT]);

		if (counter < NUM_AMBIENT)
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
		m_system->createSound(soundPath.c_str(), FMOD_LOOP_OFF, 0, &m_sfxSound[counter]);
		m_system->playSound(m_sfxSound[counter], m_channelGroup[SOUND_GROUP_NONE_LOOPING], true, &m_channel[SOUND_CHANNEL_NONE_LOOPING_01]);
		m_channel[SOUND_CHANNEL_NONE_LOOPING_01]->setChannelGroup(m_channelGroup[SOUND_GROUP_NONE_LOOPING]);
		m_channel[SOUND_CHANNEL_NONE_LOOPING_02]->setChannelGroup(m_channelGroup[SOUND_GROUP_NONE_LOOPING]);

		if (counter < NUM_SFX)
			counter++;
	}	
}
