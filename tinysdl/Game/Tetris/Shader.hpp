#ifndef SHADER_HPP
#define SHADER_HPP
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Log.hpp"
#define LOG_LENGTH 512

namespace Tetris {
	class Shader
	{
	public:
		Shader(std::string&& src);
		void use();
		void setBool(const std::string& name, bool value);
		void setInt(const std::string& name, int value);
		void setFloat(const std::string& name, float value);
		void setVec2(const std::string& name, const glm::vec2& value);
		void setVec2(const std::string& name, float x ,float y);
		void setVec3(const std::string& name, const glm::vec3& value);
		void setVec3(const std::string& name, float x, float y,float z);
		void setVec4(const std::string& name, const glm::vec4& value);
		void setVec4(const std::string& name, float x, float y, float z,float w);
		void setMat2(const std::string& name, const glm::mat2& value);
		void setMat3(const std::string& name, const glm::mat3& value);
		void setMat4(const std::string& name, const glm::mat4& value);

		~Shader();
	protected:
		void compileShader();
		void compileProgram();
		void process();
		void deleteProgram();
		void deleteShader();
		bool checkStatus(uint32_t shader, std::string&& title, GLenum status);
		void compileProgram(uint32_t vs, uint32_t fs);
		void compileShader(uint32_t shader, std::string_view src);

		std::string m_svShader{};
		std::string m_sfShader{};
		std::string m_sinfoLog{};
		std::string m_sSource{};
		uint32_t m_uifShader{};
		uint32_t m_uivShader{};
		uint32_t m_uiprogramShader{};
		int m_iSuccessCompile{};
	};
}

#endif // !SHADER_H