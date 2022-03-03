#ifndef SHADER_HPP
#define SHADER_HPP
#include <iostream>
class Shader
{
public:



	Shader();
	virtual void compileShader(std::string vs, std::string fs) = 0;
	virtual void compileProgram(uint32_t vs, uint32_t fs) = 0;
	inline void printfError() { std::cout << m_cainfoLog << '\n'; }
	virtual ~Shader();

private:
	char m_cainfoLog[512];
	uint32_t m_fShader;
	uint32_t m_vShader;
	uint32_t m_programShader;
};


#endif // !SHADER_H