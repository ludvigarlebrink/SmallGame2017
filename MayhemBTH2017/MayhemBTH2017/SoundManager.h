#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include "fmod.hpp"
#include "fmod_errors.h"

#include <iostream>
#include <string>
#include <experimental/filesystem>

enum SoundType
{
	SOUND_CHANNEL_MUSIC = 0,	// Channels 0 - 1
	SOUND_CHANNEL_AMBIENT,		// Channels 2 - 6
	SOUND_CHANNEL_LOOPING,		// Channels 7 - 16
	SOUND_CHANNEL_NONE_LOOPING,	// Channels 17 - 32
	NUM_SOUNDTYPE
};

enum Music
{
	SOUND_MUSIC_BACKGROUND_01 = 0,
	SOUND_MUSIC_BACKGROUND_02,
	NUM_MUSIC
};

enum SFX
{
	SOUND_SFX_SHOT = 0,
	SOUND_SFX_EXPLOSION,
	SOUND_SFX_BOUNCE,
	SOUND_SFX_DAMAGE,
	SOUND_SFX_CLICK,
	NUM_SFX
};

class SoundManager
{
public:
	//::.. DUMMY CONSTRUCTORS ..:://
	SoundManager();
	virtual ~SoundManager();

	//::.. FAKE FUNCTIONS ..:://
	void StartUp();
	void ShutDown();

	//::.. GET FUNCTIONS ..:://
	static SoundManager * Get();
	bool GetPlaying();
	float GetVolume();

	//::.. SET FUNCTIONS ..:://
	void SetPause(SoundType channel, bool pause);
	void SetVolume(SoundType channel, float volume);

	//::.. SOUND FUNCTIONS ..:://
	void Play(SoundType type, Music sfx);
	void Play(SoundType type, SFX sfx);
	void Update();

private:
	void Init();
	void InitMusic();
	void InitNoneLooping();
	
private:

	struct Sounds
	{
		FMOD::Sound	*	m_sound = 0;
		std::string		m_filePath;
		bool			m_playing = false;
	};

	bool							m_playing;
	float							m_volume;
	FMOD::Sound			*			m_musicSound[NUM_MUSIC];
	FMOD::Sound			*			m_sfxSound[NUM_SFX];



	static SoundManager	*			m_instance;
	FMOD::System		*			m_system;
	FMOD::Channel		*			m_channel[NUM_SOUNDTYPE];
	FMOD::ChannelGroup	*			m_channelGroup[NUM_SOUNDTYPE];
	
};

#endif