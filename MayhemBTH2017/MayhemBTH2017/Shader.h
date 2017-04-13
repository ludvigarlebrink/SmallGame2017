#ifndef __SHADER_H__
#define __SHADER_H__


#include <string>
#include <map>


class Shader
{
public:
	Shader();
	Shader(const Shader& object);	// Copy constructor.
	virtual ~Shader();

	void Load(const char* file);
	void Free();

	bool GetIsCompiled();

	

	//Shader& Get();
	//Shader& Import();

private:
	

};


#endif // !__SHADER_H__