#ifndef __SPRITEBATCH_H__
#define __SPRITEBATCH_H__

//#include "Sprite.h"
#include "Vector.h"
#include <glew.h>
#include <glm.hpp>


class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin();
	void end();

	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth);

	void renderBatch();
private:
	void createVertexArray();

	GLuint m_vbo;
	GLuint m_vao;

	

};


#endif // !__SPRITEBATCH_H__



