#include "UIImage.h"


#include "VideoManager.h"


UIImage::UIImage()
{
	m_videoManager = VideoManager::Get();

	m_windowHeight = m_videoManager->GetHeight();
	m_windowWidth = m_videoManager->GetWidth();


	// TEMP
	m_posY = 0;
	m_posX = 0;
	m_color.r = 255;
	m_color.b = 255;
	m_color.g = 255;
	m_color.a = 255;

	m_sizeX = 600;
	m_sizeY = 500;

	CreateShader();
	CreateMesh();

	m_showTexture = false;
	TextureHandler imp;
	//m_texture = imp.Import(".\\Assets\\Sprites\\MainMenu.png");
}


UIImage::~UIImage()
{
}


void UIImage::Render()
{
	glUseProgram(0);


	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);


	// FIX THIS !
	Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	int x = m_posX;
	int y = m_posY;

	SDL_Surface * surface = nullptr;

	if (m_showTexture)
	{
		m_texture.Bind(0);
	}
	else
	{
		surface = SDL_CreateRGBSurface(0, m_sizeX, m_sizeY, 32, rmask, gmask, bmask, amask);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, m_color.r, m_color.g, m_color.b, m_color.a));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
	}

	glUseProgram(m_program);
	glUniform1f(m_uniforms[SCREEN_WIDTH], static_cast<float>(m_windowWidth));
	glUniform1f(m_uniforms[SCREEN_HEIGHT], static_cast<float>(m_windowHeight));

	if (m_showTexture)
	{
		glUniform1f(m_uniforms[WIDTH], static_cast<float>(m_sizeX));
		glUniform1f(m_uniforms[HEIGHT], static_cast<float>(m_sizeY));
	}
	else
	{
		glUniform1f(m_uniforms[WIDTH], static_cast<float>(surface->w));
		glUniform1f(m_uniforms[HEIGHT], static_cast<float>(surface->h));
	}
	glUniform1f(m_uniforms[POSITION_X], static_cast<float>(m_posX));
	glUniform1f(m_uniforms[POSITION_Y], static_cast<float>(m_posY));
	glUniform1f(m_uniforms[SCALE], 1.0f);

	glUniform1i(m_uniforms[ALBEDO_MAP], 0);

	m_mesh->Render();


	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);


	glDeleteTextures(1, &texture);
	SDL_FreeSurface(surface);
}


void UIImage::RenderWithUV()
{
	glUseProgram(0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	// m_Width and m_Height is the resolution of window.
	glOrtho(0, m_windowWidth, 0, m_windowHeight, -1, 1);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);


	// FIX THIS !
	Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	int x = m_posX;
	int y = m_posY;

	SDL_Surface * surface = nullptr;

	if (m_showTexture)
	{
		m_texture.Bind(0);
	}
	else
	{
		surface = SDL_CreateRGBSurface(0, m_sizeX, m_sizeY, 32, rmask, gmask, bmask, amask);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, m_color.r, m_color.g, m_color.b, m_color.a));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
	}

	float halfHeight = m_windowHeight / 2;
	float halfWidth = m_windowWidth / 2;

	glBegin(GL_QUADS);
	{

		glTexCoord2f((32.0 * (m_UV.x + 0) / 512), (32.0 * (m_UV.y + 0) / 512));
		glVertex2f(
			static_cast<GLfloat>(x - ((m_sizeX / 2) - halfWidth)),
			static_cast<GLfloat>(y - ((m_sizeY / 2) - halfHeight)));

		glTexCoord2f((32.0 * (m_UV.x + 1) / 512), (32.0 * (m_UV.y + 0) / 512));
		glVertex2f(
			static_cast<GLfloat>(x + ((m_sizeX / 2) + halfWidth)),
			static_cast<GLfloat>(y - ((m_sizeY / 2) - halfHeight)));

		glTexCoord2f((32.0 * (m_UV.x + 1) / 512), -(32.0 * (m_UV.y + 1) / 512));

		glVertex2f(
			static_cast<GLfloat>(x + ((m_sizeX / 2) + halfWidth)),
			static_cast<GLfloat>(y + ((m_sizeY / 2) + halfHeight)));

		glTexCoord2f((32.0 * (m_UV.x + 0) / 512), -(32.0 * (m_UV.y + 1) / 512));

		glVertex2f(
			static_cast<GLfloat>(x - ((m_sizeX / 2) - halfWidth)),
			static_cast<GLfloat>(y + ((m_sizeY / 2) + halfHeight)));

	}
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDeleteTextures(1, &texture);
	SDL_FreeSurface(surface);
}

//::.. GET FUNCTIONS ..:://
int32_t UIImage::GetSizeX()
{
	return m_sizeX;
}

int32_t UIImage::GetSizeY()
{
	return m_sizeY;
}

int32_t UIImage::GetPosX()
{
	return m_posX;
}

int32_t UIImage::GetPosY()
{
	return m_posY;
}

Texture UIImage::GetTexture()
{
	return m_texture;
}

glm::vec2 UIImage::GetUV()
{
	return m_UV;
}


//::.. SET FUNCTIONS ..:://
void UIImage::SetPosition(int32_t x, int32_t y)
{
	m_posX = x;
	m_posY = y;
}

void UIImage::SetSize(int32_t x, int32_t y)
{
	m_sizeX = x;
	m_sizeY = y;
}


void UIImage::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	m_color.a = a;
}


void UIImage::SetAlpha(float alpha)
{
	m_color.a = static_cast<uint8_t>(alpha * 255);
}


void UIImage::SetAlpha(uint8_t alpha)
{
	m_color.a = alpha;
}

void UIImage::SetTexture(const char * filepath)
{
	TextureHandler imp;
	m_texture = imp.Import(filepath);
	m_showTexture = true;
}

void UIImage::SetTexture(Texture texture)
{
	m_texture = texture;
	m_showTexture = true;
}



void UIImage::SetUV(glm::vec2 uv)
{
	m_UV = uv;
}


void UIImage::CreateMesh()
{
	m_mesh = new Mesh;

	Vertex2D vert[6];
	vert[0].position = glm::vec2(-1.0f, -1.0f);
	vert[0].texCoords = glm::vec2(0.0f, 1.0f);
	vert[1].position = glm::vec2(1.0f, -1.0f);
	vert[1].texCoords = glm::vec2(1.0f, 1.0f);
	vert[2].position = glm::vec2(-1.0f, 1.0f);
	vert[2].texCoords = glm::vec2(0.0f, 0.0f);
	vert[3].position = glm::vec2(1.0f, -1.0f);
	vert[3].texCoords = glm::vec2(1.0f, 1.0f);
	vert[4].position = glm::vec2(-1.0f, 1.0f);
	vert[4].texCoords = glm::vec2(0.0f, 0.0f);
	vert[5].position = glm::vec2(1.0f, 1.0f);
	vert[5].texCoords = glm::vec2(1.0f, 0.0f);

	m_mesh->Load(vert, 6);
}


void UIImage::CreateShader()
{
	std::string shaders[2];
	uint32_t types[2];

	shaders[0] = ".\\Assets\\GLSL\\SpriteShader.vert";
	shaders[1] = ".\\Assets\\GLSL\\SpriteShader.frag";

	types[0] = ShaderManager::VERT_SHADER;
	types[1] = ShaderManager::FRAG_SHADER;

	m_program = ShaderManager::CreateAndAttachShaders("SpriteShader", shaders, types, 2);

	glBindAttribLocation(m_program, 0, "Position");
	glBindAttribLocation(m_program, 1, "TexCoords");

	ShaderManager::LinkAndValidate("SpriteShader");

	m_uniforms[SCREEN_WIDTH] = glGetUniformLocation(m_program, "ScreenWidth");
	m_uniforms[SCREEN_HEIGHT] = glGetUniformLocation(m_program, "ScreenHeight");
	m_uniforms[WIDTH] = glGetUniformLocation(m_program, "Width");
	m_uniforms[HEIGHT] = glGetUniformLocation(m_program, "Height");
	m_uniforms[POSITION_X] = glGetUniformLocation(m_program, "PosX");
	m_uniforms[POSITION_Y] = glGetUniformLocation(m_program, "PosY");
	m_uniforms[SCALE] = glGetUniformLocation(m_program, "Scale");
	m_uniforms[ALBEDO_MAP] = glGetUniformLocation(m_program, "AlbedoMap");
}