#ifndef SHADER_H
#define SHADER_H
#include <iostream>
class Shader
{
public:

	const char* s_vRedBlock = "#version 330 core \n"
		"layout(location = 0) in vec3 vPos; \n"
		"void main() {\n"
		" gl_Postion =vec4(vPos.x,vPos.y,vPos.z,1.0);\n"
		"}";
	const char* s_fRedBlock = "#version 330 core \n"
		"uniform vec4 fcolor"
		"out vec4 FragColor; \n"
		"void main() {\n"
		" FragColor =vec4(fcolor.r,fcolor.g,fcolor.b,fcolor.a);\n"
		"}";
	Shader();
	~Shader();
	void compileShader(std::string vs, std::string fs);
	void compileProgram(std::string vs, std::string fs);
private:
	uint32_t m_fShader;
	uint32_t m_vShader;
	uint32_t m_programShader;
};


#endif // !SHADER_H