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

void SoundManager::SetPause(SoundChannels channel, bool pause)
{
	m_channel[channel]->setPaused(pause);
}

void SoundManager::SetVolume(SoundGroups channel, float volume)
{
	m_channelGroup[channel]->setVolume(volume);
}

void SoundManager::PlayMusic(std::string soundName, bool paused)
{
	bool playing;
	std::string path = ".\\Assets\\Sounds\\Music\\";
	std::string soundFile;

	soundFile = path + soundName + ".wav";

	for (int i = 0; i < m_musicSounds.size(); i++)
	{
		if (m_musicSounds.at(i).m_soundPath.c_str() == soundFile)
		{
			m_system->playSound(m_musicSounds.at(i).m_sound, m_channelGroup[SOUND_GROUP_MUSIC], paused, &m_channel[SOUND_CHANNEL_MUSIC_01]);
		}
	}
}

void SoundManager::PlaySFX(std::string soundName, bool paused)
{
	bool playing;
	std::string path = ".\\Assets\\Sounds\\SFX\\";
	std::string soundFile;

	FMOD::Sound*  yolo;

	soundFile = path + soundName + ".wav";

	for (int i = 0; i < m_sfxSounds.size(); i++)
	{
		if (m_sfxSounds.at(i).m_soundPath.c_str() == soundFile)
		{
			if (m_channel[SOUND_CHANNEL_SFX_01]->isPlaying(&playing))
				m_system->playSound(m_sfxSounds.at(i).m_sound, m_channelGroup[SOUND_GROUP_SFX], paused, &m_channel[SOUND_CHANNEL_SFX_02]);
			else if (m_channel[SOUND_CHANNEL_SFX_02]->isPlaying(&playing))
				m_system->playSound(m_sfxSounds.at(i).m_sound, m_channelGroup[SOUND_GROUP_SFX], paused, &m_channel[SOUND_CHANNEL_SFX_01]);
		}
	}
}

void SoundManager::PlayAmbient(std::string soundName, bool paused)
{
	bool playing;
	std::string path = ".\\Assets\\Sounds\\Ambient\\";
	std::string soundFile;

	soundFile = path + soundName + ".wav";

	for (int i = 0; i < m_ambientSounds.size(); i++)
	{
		if (m_ambientSounds.at(i).m_soundPath.c_str() == soundFile)
		{
			m_system->playSound(m_ambientSounds.at(i).m_sound, m_channelGroup[SOUND_GROUP_AMBIENT], paused, &m_channel[SOUND_CHANNEL_AMBIENT_01]);
		}
	}
}


void SoundManager::FadeInNewMusic(std::string newSound, float fadeOutSeconds, float fadeInSeconds)
{
	unsigned long long dspClock;
	int rate;
	float volume;

	m_channelGroup[SOUND_GROUP_MUSIC]->getVolume(&volume);

	m_system->getSoftwareFormat(&rate, 0, 0);
	m_channel[SOUND_CHANNEL_MUSIC_01]->getDSPClock(0, &dspClock);
	m_channel[SOUND_CHANNEL_MUSIC_01]->addFadePoint(dspClock, volume);
	m_channel[SOUND_CHANNEL_MUSIC_01]->addFadePoint(dspClock + (rate * fadeOutSeconds), 0.0);
	m_channel[SOUND_CHANNEL_MUSIC_01]->setDelay(0, dspClock + (rate * fadeOutSeconds), true);

	PlayMusic(newSound);

	m_channel[SOUND_CHANNEL_MUSIC_01]->getDSPClock(0, &dspClock);
	m_channel[SOUND_CHANNEL_MUSIC_01]->addFadePoint(dspClock, 0);
	m_channel[SOUND_CHANNEL_MUSIC_01]->addFadePoint(dspClock + (rate * fadeInSeconds), volume);

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

	for (int i = 0; i < NUM_GROUPS; i++)
		m_system->createChannelGroup(NULL, &m_channelGroup[i]);

	InitMusic();
	InitSFX();
	InitAmbient();
}

void SoundManager::InitMusic()
{
	std::string path = ".\\Assets\\Sounds\\Music\\";
	Sounds sounds;

	for (auto & p : std::experimental::filesystem::directory_iterator(path))
	{
		sounds.m_soundPath = p.path().string();
		m_system->createStream(sounds.m_soundPath.c_str(), FMOD_DEFAULT, 0, &sounds.m_sound);
		m_musicSounds.push_back(sounds);
		m_channel[SOUND_CHANNEL_MUSIC_01]->setChannelGroup(m_channelGroup[SOUND_GROUP_MUSIC]);
		m_channel[SOUND_CHANNEL_MUSIC_02]->setChannelGroup(m_channelGroup[SOUND_GROUP_MUSIC]);
	}
}

void SoundManager::InitAmbient()
{
	std::string path = ".\\Assets\\Sounds\\Ambient\\";
	Sounds sounds;

	for (auto & p : std::experimental::filesystem::directory_iterator(path))
	{
		sounds.m_soundPath = p.path().string();
		m_system->createStream(sounds.m_soundPath.c_str(), FMOD_DEFAULT, 0, &sounds.m_sound);
		m_ambientSounds.push_back(sounds);
		m_channel[SOUND_CHANNEL_AMBIENT_01]->setChannelGroup(m_channelGroup[SOUND_GROUP_AMBIENT]);
		m_channel[SOUND_CHANNEL_AMBIENT_02]->setChannelGroup(m_channelGroup[SOUND_GROUP_AMBIENT]);
	}
}

void SoundManager::InitSFX()
{
	std::string path = ".\\Assets\\Sounds\\SFX\\";
	Sounds sounds;

	for (auto & p : std::experimental::filesystem::directory_iterator(path))
	{
		sounds.m_soundPath = p.path().string();
		m_system->createSound(sounds.m_soundPath.c_str(), FMOD_LOOP_OFF, 0, &sounds.m_sound);
		m_sfxSounds.push_back(sounds);
		m_channel[SOUND_CHANNEL_SFX_01]->setChannelGroup(m_channelGroup[SOUND_GROUP_SFX]);
		m_channel[SOUND_CHANNEL_SFX_02]->setChannelGroup(m_channelGroup[SOUND_GROUP_SFX]);
	}
}