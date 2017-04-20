#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include "Texture.h"
#include "SDL.h"


class Material
{
public:
	Material();
	virtual ~Material();

	void SetMaterial(const char * filepath);

private:
	Texture		m_texture;

};

#endif // !__MATERIAL_H__