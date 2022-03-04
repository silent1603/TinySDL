#include "Shader.hpp"
#include "Log.hpp"
namespace Tetris {
	Shader::Shader()
	{
		m_sinfoLog.resize(LOG_LENGTH);
	}

	void Shader::getSource(std::string& src)
	{
	}

	void Shader::compileShader()
	{
		compileShader(m_uivShader, std::string_view{ m_svShader });
		checkStatus(m_uivShader, "VERTEX_SHADER: ",GL_COMPILE_STATUS);
		compileShader(m_uifShader, std::string_view{ m_svShader });
		checkStatus(m_uivShader, "FRAGMENT_SHADER: ",GL_COMPILE_STATUS);
	}

	void Shader::compileProgram()
	{
		compileProgram(m_uivShader, m_uifShader);
		checkStatus(m_uivShader, "PROGRAM_SHADER: ", GL_LINK_STATUS);
	}


	Shader::~Shader()
	{
	}

	bool Shader::checkStatus(uint32_t shader,std::string&& title,GLenum status)
	{
		glGetShaderiv(shader, status, &m_iSuccessCompile);
		if (!m_iSuccessCompile)
		{
			glGetShaderInfoLog(shader, LOG_LENGTH, 0, &m_sinfoLog[0]);
			TETRIS_ERROR(title, m_sinfoLog);
			return false;
		}
		return true;
	}

	void Shader::compileProgram(uint32_t vs,uint32_t fs)
	{
		m_uiprogramShader = glCreateProgram();
		glAttachShader(m_uiprogramShader, vs);
		glAttachShader(m_uiprogramShader, fs);
		glLinkProgram(m_uiprogramShader);
	}

	void Shader::compileShader(uint32_t shader, std::string_view src)
	{
		shader = glCreateShader(GL_VERTEX_SHADER);
		const char* c_str = src.data();
		glShaderSource(shader, 1, &c_str, 0);
		glCompileShader(shader);
		
	}
}
