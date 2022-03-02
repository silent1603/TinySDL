#ifndef SHADER_H
#define SHADER_H
#include <iostream>
class Shader
{
public:

	const char* s_vRedBlock = "#version 330 core \n"
		"layout(location = 0) in vec3 aPos; \n"
		"void main() {\n"
		" gl_Postion =vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"}";
	const char* s_fRedBlock = "#version 330 core \n"
		"out vec4 FragColor; \n"
		"void main() {\n"
		" FragColor =vec4(1.0,0.0,0.0,1.0);\n"
		"}";
	//need chagned  -> save to file 
	const char* s_vGreenBlock = "#version 330 core \n"
		"layout(location = 0) in vec3 aPos; \n"
		"void main() {\n"
		" gl_Postion =vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"}";
	const char* s_fGreenBlock = "#version 330 core \n"
		"out vec4 FragColor; \n"
		"void main() {\n"
		" FragColor =vec4(1.0,0.0,0.0,1.0);\n"
		"}";

	const char* s_vBlueBlock = "#version 330 core \n"
		"layout(location = 0) in vec3 aPos; \n"
		"void main() {\n"
		" gl_Postion =vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"}";
	const char* s_fBlueBlock = "#version 330 core \n"
		"out vec4 FragColor; \n"
		"void main() {\n"
		" FragColor =vec4(1.0,0.0,0.0,1.0);\n"
		"}";


	const char* s_vYellowBlock = "#version 330 core \n"
		"layout(location = 0) in vec3 aPos; \n"
		"void main() {\n"
		" gl_Postion =vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"}";
	const char* s_fYellowBlock = "#version 330 core \n"
		"out vec4 FragColor; \n"
		"void main() {\n"
		" FragColor =vec4(1.0,0.0,0.0,1.0);\n"
		"}";

	const char* s_vVioletBlock = "#version 330 core \n"
		"layout(location = 0) in vec3 aPos; \n"
		"void main() {\n"
		" gl_Postion =vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"}";
	const char* s_fVioletBlock = "#version 330 core \n"
		"out vec4 FragColor; \n"
		"void main() {\n"
		" FragColor =vec4(1.0,0.0,0.0,1.0);\n"
		"}";

	const char* s_vBrownBlock = "#version 330 core \n"
		"layout(location = 0) in vec3 aPos; \n"
		"void main() {\n"
		" gl_Postion =vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"}";
	const char* s_fBrownBlock = "#version 330 core \n"
		"out vec4 FragColor; \n"
		"void main() {\n"
		" FragColor =vec4(1.0,0.0,0.0,1.0);\n"
		"}";

	const char* s_vBackgroundBlock = "#version 330 core \n"
		"layout(location = 0) in vec3 aPos; \n"
		"void main() {\n"
		" gl_Postion =vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"}";
	const char* s_fBackgroundBlock = "#version 330 core \n"
		"out vec4 FragColor; \n"
		"void main() {\n"
		" FragColor =vec4(1.0,0.0,0.0,1.0);\n"
		"}";

	Shader();
	void compileShader(std::string vs, std::string fs);
	void compileProgram(std::string vs, std::string fs);

private:
	uint32_t m_fShader;
	uint32_t m_vShader;
	uint32_t m_programShader;
};


#endif // !SHADER_H