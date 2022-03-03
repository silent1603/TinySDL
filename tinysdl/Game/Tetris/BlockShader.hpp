#ifndef BLOCKSHADER_HPP
#define BLOCKSHADER_HPP
#include "Shader.hpp"
class BlockShader:public Shader
{
private:
	const char* s_vRedBlock = "#version 330 core \n"
		"layout(location = 0) in vec3 aPos; \n"
		"void main() {\n"
		" gl_Postion =vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"}";
	const char* s_fRedBlock = "#version 330 core \n"
		"out vec4 FragColor; \n"
		"uniform vec4 fcolor;"
		"void main() {\n"
		" FragColor =vec4(fcolor.r,fcolor.g,fcolor.b,fcolor.a);\n"
		"}";
public:
	BlockShader();
	void compileShader(std::string vs, std::string fs) override;
	void compileProgram(std::string vs, std::string fs) override;
	~BlockShader() override;
};
#endif
