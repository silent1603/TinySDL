#ifndef SHADER_HPP
#define SHADER_HPP
#include <iostream>
#include <string>
#include <glad/glad.h>
#include "Log.hpp"
#define LOG_LENGTH 512

namespace Tetris {
	class Shader
	{
	public:
		Shader();
		virtual void getSource(std::string& src);
		virtual void compileShader();
		virtual void compileProgram();
		virtual ~Shader();
	protected:
		
		bool checkStatus(uint32_t shader,std::string&& title,GLenum status);
		virtual void compileProgram(uint32_t vs,uint32_t fs) ;
		virtual void compileShader(uint32_t shader, std::string_view src) ;
		std::string m_svShader;
		std::string m_sfShader;
		std::string m_sinfoLog;
		uint32_t m_uifShader;
		uint32_t m_uivShader;
		uint32_t m_uiprogramShader;
		int m_iSuccessCompile;
		bool m_hasSource;
	};
}

#endif // !SHADER_H