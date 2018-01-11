#include "../include/graphics/shader.h"

#define GLEW_STATIC
#include"GL\glew.h"

#include"../include/utility/utility.h"

#include<vector>

namespace sudo { namespace graphics {

	Shader::~Shader()
	{
		glDeleteProgram(m_shaderProgram);
	}

	Shader::Shader(const char* a_vertexPath, const char* a_fragmentPath) 
	{
		std::string vertex_shader_source = utility::GetFileContent(a_vertexPath);
		std::string fragment_shader_source = utility::GetFileContent(a_fragmentPath);
	
		CreateShader(vertex_shader_source.c_str(), fragment_shader_source.c_str());
	}

	Shader::Shader(const char* a_vertexFileData, const char* a_fragmentFileData, int x) 
	{
		CreateShader(a_vertexFileData, a_fragmentFileData);
	}

	void Shader::CreateShader(const char* a_vertexFileData, const char* a_fragmentFileData)
	{
		// Loading and compiling vertex shader
		uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexShaderSource = a_vertexFileData;
		glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
		glCompileShader(vertexShader);
		didCompile(vertexShader);

		// Loading and compiling fragment shader
		uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragmentShaderSource = a_fragmentFileData;
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
		glCompileShader(fragmentShader);
		didCompile(fragmentShader);

		// Doing the shader program stuff
		m_shaderProgram = glCreateProgram();
		glAttachShader(m_shaderProgram, vertexShader);
		glAttachShader(m_shaderProgram, fragmentShader);
		glLinkProgram(m_shaderProgram);

		// Delete the individual shaders, we don't need them anymore now that we have the program
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Shader::enable() const
	{
		glUseProgram(m_shaderProgram);
	}

	void Shader::disable() const
	{
		glUseProgram(0);
	}

	bool Shader::didCompile(uint a_shader)
	{
		GLint isCompiled = 0;
		glGetShaderiv(a_shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(a_shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(a_shader, maxLength, &maxLength, &errorLog[0]);

			std::string temp;
			// Provide the infolog.
			for (int i = 0; i < errorLog.size(); i++) {
				//std::cout << errorLog[i];
				temp += errorLog[i];
			}
			DEBUG *debug = DEBUG::getInstance();
			debug->logMessage(temp.c_str(), LogType::Error);
			debug->printMessage(temp.c_str(), LogType::Error);

			// Exit with failure.
			glDeleteShader(a_shader); // Don't leak the shader.
			return false;
		}
		return true;
	}

	void Shader::setUniformMatrix4x4(const GLchar* a_name, math::Matrix4x4& a_matrix) 
	{
		glUniformMatrix4fv(getUniformLocation(a_name), 1, GL_FALSE, a_matrix.elements);
	}

	void Shader::setUniform1f(const GLchar* a_name, float value)
	{
		glUniform1f(getUniformLocation(a_name), value);
	}

	void Shader::setUniform2f(const GLchar* a_name, const math::Vector2& vec) 
	{
		glUniform2f(getUniformLocation(a_name), vec.x, vec.y);
	}

	void Shader::setUniform3f(const GLchar* a_name, const math::Vector3& vec) 
	{
		glUniform3f(getUniformLocation(a_name), vec.x, vec.y, vec.z);
	}

	void Shader::setUniform1fv(const GLchar *a_name, int count, float *value) 
	{
		glUniform1fv(getUniformLocation(a_name), count, value);
	}

	void Shader::setUniform1iv(const GLchar *a_name, int count, int *value)
	{
		glUniform1iv(getUniformLocation(a_name), count, value);
	}

	uint Shader::getUniformLocation(const char* a_name) 
	{
		return glGetUniformLocation(m_shaderProgram, a_name);
	}
} }