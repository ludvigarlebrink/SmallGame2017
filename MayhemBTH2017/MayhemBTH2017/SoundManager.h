#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include "fmod.hpp"
#include "fmod_errors.h"

#include <iostream>
#include <string>
#include <experimental/filesystem>

enum SoundType
{
	SOUND_CHANNEL_MUSIC_01 = 0,	// Channels 0 - 1
	SOUND_CHANNEL_MUSIC_02,
	SOUND_CHANNEL_AMBIENT_01,		// Channels 2 - 6
	SOUND_CHANNEL_AMBIENT_02,
	SOUND_CHANNEL_LOOPING_01,		// Channels 7 - 16
	SOUND_CHANNEL_LOOPING_02,
	SOUND_CHANNEL_NONE_LOOPING_01,	// Channels 17 - 32
	SOUND_CHANNEL_NONE_LOOPING_02,
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

enum Ambient
{
	SOUND_AMBIENT_FOREST = 0,
	NUM_AMBIENT
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
		bool			m_playing = false;
	};

	bool							m_playing;
	float							m_volume;
	Sounds							m_musicSound[NUM_MUSIC];
	Sounds							m_sfxSound[NUM_SFX];



	static SoundManager	*			m_instance;
	FMOD::System		*			m_system;
	FMOD::Channel		*			m_channel[NUM_SOUNDTYPE];
	FMOD::ChannelGroup	*			m_channelGroup[NUM_SOUNDTYPE];
	
};

#endif