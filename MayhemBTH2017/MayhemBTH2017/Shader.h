#ifndef __SHADER_H__
#define __SHADER_H__


#include <string>
#include <map>


class Shader
{
public:
	enum ShaderType
	{
		VERT_STATIC_SHADER = 0,
		VERT_ANIM_SHADER,
		FRAG_TOON_SHADER
	};


	Shader();
	Shader(const Shader& object);	// Copy constructor.
	virtual ~Shader();

	void Load(const char* file);
	void Free();
	

	//Shader& Get();
	//Shader& Import();

private:
	

};


#endif // !__SHADER_H__