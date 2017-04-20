#include "Material.h"



Material::Material()
{
}


Material::~Material()
{
}

void Material::SetMaterial(const char * filepath)
{
	SDL_Surface* img = SDL_LoadBMP(filepath);

//	m_texture.LoadTexture(img, img->)

}
