#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "PrefabManager.h"
#include "Box.h"
#include "AShader.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "PlayerPrefab.h"
#include "Collidable.h"
#include "Projectile.h"
#include "Weapon.h"
#include "ScoreManager.h"
#include "PostProcessingManager.h"
#include "SoundManager.h"
#include "AtomicBomb.h"

class Player : public Collidable
{
public:
	//::.. CONSTRUCTORS ..:://
	Player();
	Player(b2World* world, glm::vec2 pos, glm::vec2 scale, int controllerID);
	virtual ~Player();

	//::.. INITIALIZER ..:://
	void Init(b2World* world, glm::vec2 pos, glm::vec2 scale, int controllerID);

	void Free();

	//::.. RENDER ..:://
	void Render(Camera camera);
	void RenderShadow(Camera camera);

	void Update(Player * p_arr);
	void Respawn(glm::vec2 pos);

	//::.. SET FUNCTIONS ..:://
	void SetCategoryBits(short CATEGORY);
	void SetMaskBits(short MASK);
	bool Timer(float rate);
	void SetControllerID(int ID);
	void  Hit(int projectileID);
	void SetSkullCheck(bool value);
	void SetPointToGet(uint32_t value);

	//::..GETTERS..:://
	uint16 GetCategoryBits();
	uint16 GetMaskBits();
	Box GetBox();
	float GetDamage();
	PlayerPrefab* GetPrefab();
	int GetProjectileID();
	void StartContact(bool projectile, bool powerup, bool skull);
	void EndContact();
	int GetControllerID();
	void UpdateParticles();
	Prefab * GetHealthBar();
	Prefab* GetHealthBarBackground();
	Prefab* GetLaserSight();
	Prefab* GetPlayerArrow();
	Prefab* GetMuzzleFlash();
	bool	GetDead();
	bool GetSkullCheck();
	b2Vec2 GetDeathPos();

private:

	Texture * m_particleTexture1;
	Texture * m_particleTexture2;
	Texture * m_particleTexture3;
	Texture * m_particleTexture4;
	Texture * m_particleTexture5;
	Texture * m_particleTexture6;
	Texture * m_particleTexture7;

	TextureHandler	m_textureHandler;
	ParticleSystem	m_particles;
	InputManager *	m_input;
	b2Fixture *		m_filter;
	Box				m_boundingBox;
	Box				m_skullBoundingBox;
	PlayerPrefab *	m_playerPrefab;
	Sprite			m_playerSprite;
	Transform		m_transf;
	Camera			m_cam;
	AShader			m_shader;
	AShader			m_toonShader;


	bool	m_isMidAir;
	bool	m_doubleJump;
	bool	m_contact;
	bool	m_dead;
	bool	m_skullCheck = true;
	bool	m_firing;
	float	m_fireTimer;
	float	m_time;
	int		m_controllerID;
	bool	m_collidedProjectile;
	bool	m_hitByProjectile;
	float	m_life;

	Prefab *		m_healthBar;
	Prefab*			m_muzzleFlash;
	Prefab *		m_laserSight;
	Prefab*			m_healthBarBackground;
	Prefab*			m_playerArrow;
	int				m_hitByProjectileID;
	SoundManager *	m_soundManager;

	Weapon *		m_weapons[7];
	int				m_currentWeapon;

	b2World *	m_world;
	b2Vec2		m_deathPos;

	bool		m_collidedPowerUp;
	bool		m_collidedSkull;
	uint32_t	m_pointsToGet;

	float m_deathTImer = 0;

	b2FixtureDef m_fixture;
	//enum _entityCategory {
	//	BOUNDARY = 0x0001,
	//	POWERUP = 0x0008,
	//	PLAYER1 = 0x0002,
	//	PLAYER3 = 0x0064,
	//	PLAYER2 = 0x0016,
	//	PLAYER4 = 0x00128,
	//	PROJECTILE1 = 0x0004,
	//	PROJECTILE2 = 0x0032,
	//	PROJECTILE3 = 0x00256,
	//	PROJECTILE4 = 0x00512,
	//};

	enum _entityCategory {
		BOUNDARY = 0x0001,
		POWERUP = 0x0002,
		PLAYER1 = 0x0004,
		PLAYER3 = 0x0008,
		PLAYER2 = 0x0010,
		PLAYER4 = 0x0020,
		PROJECTILE1 = 0x0040,
		PROJECTILE2 = 0x0080,
		PROJECTILE3 = 0x0100,
		PROJECTILE4 = 0x0120,
		SKULL = 0x0140,
	};

};

#endif