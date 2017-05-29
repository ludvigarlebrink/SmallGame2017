#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include "fmod.hpp"
#include "fmod_errors.h"


#include <string>
#include <experimental/filesystem>

enum SoundChannels
{
	SOUND_CHANNEL_MUSIC_01 = 0,
	SOUND_CHANNEL_MUSIC_02,
	SOUND_CHANNEL_AMBIENT_01,
	SOUND_CHANNEL_AMBIENT_02,
	SOUND_CHANNEL_SFX_01,
	SOUND_CHANNEL_SFX_02,
	NUM_SOUNDTYPE
};

enum SoundGroups
{
	SOUND_GROUP_MUSIC = 0,
	SOUND_GROUP_AMBIENT,
	SOUND_GROUP_SFX,
	NUM_GROUPS

};

//enum Music
//{
//	SOUND_MUSIC_BACKGROUND_01 = 0,
//	SOUND_MUSIC_BACKGROUND_02,
//	NUM_MUSIC
//};
//
//enum SFX
//{
//	SOUND_SFX_SHOT = 0,
//	SOUND_SFX_EXPLOSION,
//	SOUND_SFX_BOUNCE,
//	SOUND_SFX_DAMAGE,
//	SOUND_SFX_CLICK,
//	NUM_SFX
//};
//
//enum Ambient
//{
//	SOUND_AMBIENT_FOREST = 0,
//	NUM_AMBIENT
//};

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

	//::.. SET FUNCTIONS ..:://
	void SetPause(SoundGroups channel, bool pause);
	void SetPause(SoundChannels channel, bool pause);
	void SetVolume(SoundGroups channel, float volume);

	//::.. SOUND FUNCTIONS ..:://
	void PlayMusic(std::string soundName, bool paused = false);
	void PlaySFX(std::string soundName, bool paused = false);
	void PlayAmbient(std::string soundName, bool paused = false);
	void FadeInNewMusic(std::string newSound, float fadeOutSeconds, float fadeInSeconds);
	void Update();

private:
	void Init();
	void InitMusic();
	void InitAmbient();
	void InitSFX();

private:

	struct Sounds
	{
		FMOD::Sound *	m_sound;
		std::string		m_soundPath;
	};

	std::vector<Sounds>				m_sfxSounds;
	std::vector<Sounds>				m_musicSounds;
	std::vector<Sounds>				m_ambientSounds;

	static SoundManager	*			m_instance;
	FMOD::System		*			m_system;
	FMOD::Channel		*			m_channel[NUM_SOUNDTYPE];
	FMOD::ChannelGroup	*			m_channelGroup[NUM_GROUPS];

};

#endif