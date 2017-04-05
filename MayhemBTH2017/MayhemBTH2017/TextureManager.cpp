#include "TextureManager.h"

TextureManager * TextureManager::m_instance = nullptr;

//::.. DUMMY CONSTRUCTORS ..:://

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}


//::.. FAKE FUNCTIONS ..:://

void TextureManager::StartUp()
{
	{
		if (m_instance == nullptr)
		{
			m_instance = this;
			//Init();
		}
	}
}

void TextureManager::ShutDown()
{
	//TBA
}

//::.. HELPER FUNCTIONS ..:://

void TextureManager::AddTexture(GLuint id, const std::string& filePath)
{
	Textures texture;
	ImageLoader imageLoader;
	texture.createTexture(id);
	imageLoader.loadBMP(filePath, texture);

}

void TextureManager::bindTexture(GLuint id)
{
	ImageLoader imageLoader;
	imageLoader.Bind(id);
}

//::.. GET FUNCTIONS ..:://

TextureManager * TextureManager::Get()
{
	return m_instance;
}

