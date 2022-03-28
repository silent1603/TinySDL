#include "Shader.hpp"
#include "Log.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <utility>
namespace Tetris {
	Shader::Shader(std::string&& src)
	{
		m_sinfoLog.resize(LOG_LENGTH);
		m_sSource = std::move(src);
	}

	void Shader::use()
	{
		glUseProgram(m_uiprogramShader);
	}

	void Shader::setBool(const std::string& name, bool value)
	{
		glUniform1i(glGetUniformLocation(m_uiprogramShader,name.c_str()), static_cast<int>(value));
	}

	void Shader::setInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(m_uiprogramShader, name.c_str()), value);
	}

	void Shader::setFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(m_uiprogramShader, name.c_str()), value);
	}

	void Shader::setVec2(const std::string& name, const glm::vec2& value)
	{
		glUniform2fv(glGetUniformLocation(m_uiprogramShader, name.c_str()),1,&value[0]);
	}

	void Shader::setVec2(const std::string& name, float x, float y)
	{
		glUniform2f(glGetUniformLocation(m_uiprogramShader, name.c_str()), x, y);
	}

	void Shader::setVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(m_uiprogramShader, name.c_str()), 1, &value[0]);
	}

	void Shader::setVec3(const std::string& name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(m_uiprogramShader, name.c_str()),x,y,z);
	}

	void Shader::setVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4fv(glGetUniformLocation(m_uiprogramShader, name.c_str()), 1, &value[0]);
	}

	void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(m_uiprogramShader, name.c_str()), x, y, z,w);
	}

	void Shader::setMat2(const std::string& name, const glm::mat2& value)
	{
		glUniformMatrix2fv(glGetUniformLocation(m_uiprogramShader, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

	void Shader::setMat3(const std::string& name, const glm::mat3& value)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_uiprogramShader, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

	void Shader::setMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_uiprogramShader, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}



	void Shader::process()
	{

		std::ifstream file(m_sSource);
		if (file.is_open()) {
			nlohmann::json json;
			file >> json;
			//nlohmann::json json = nlohmann::json::parse(file);
			m_svShader = json.at("block").at("vertex");
			m_sfShader = json.at("block").at("fragment");
			compileShader();
			compileProgram();
			TETRIS_INFO("SHADER", "LOAD SUCCESS");
		}
		TETRIS_ERROR("SHADER", "LOAD FAILED");
	}

	void Shader::compileShader()
	{
		compileShader(m_uivShader, std::string_view{ m_svShader });
		checkStatus(m_uivShader, "VERTEX_SHADER: ", GL_COMPILE_STATUS);
		compileShader(m_uifShader, std::string_view{ m_svShader });
		checkStatus(m_uivShader, "FRAGMENT_SHADER: ", GL_COMPILE_STATUS);
	}

	void Shader::compileProgram()
	{
		compileProgram(m_uivShader, m_uifShader);
		checkStatus(m_uivShader, "PROGRAM_SHADER: ", GL_LINK_STATUS);
	}

	void Shader::deleteShader()
	{
		glDeleteShader(m_uivShader);
		glDeleteShader(m_uifShader);
	}

	void Shader::deleteProgram()
	{
		glDeleteProgram(m_uiprogramShader);
	}


	Shader::~Shader()
	{
		deleteShader();
		deleteProgram();
	}

	bool Shader::checkStatus(uint32_t shader, std::string&& title, GLenum status)
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

	void Shader::compileProgram(uint32_t vs, uint32_t fs)
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
