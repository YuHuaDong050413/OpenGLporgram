#include "Shader.h"
#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& vertPath, const std::string& fragPath)
	: m_VertexPath(vertPath), m_FragmentPath(fragPath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(m_VertexPath, m_FragmentPath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::Shader(const std::string& filepath):Shader(filepath, "null") {}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}
///---------------已经弃用---------------------------///
//ShaderProgramSource Shader::ParseShader(const std::string& filepath)
//{
//	std::ifstream stream(filepath);
//
//	enum class ShaderType
//	{
//		NONE = -1, VERTEX = 0, FRAGMENT = 1,
//	};
//
//	std::string line;
//	std::stringstream ss[2];
//	ShaderType type = ShaderType::NONE;
//
//	while (getline(stream, line))
//	{
//		if (line.find("#shader") != std::string::npos)
//		{
//			if (line.find("vertex") != std::string::npos)
//			{
//				type = ShaderType::VERTEX;
//			}
//			else if (line.find("fragment") != std::string::npos)
//			{
//				type = ShaderType::FRAGMENT;
//			}
//		}
//		else
//		{
//			ss[(int)type] << line << '\n';
//		}
//	}
//
//	return { ss[0].str(), ss[1].str() };
//}

ShaderProgramSource Shader::ParseShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	std::string line;
	std::stringstream ss[2];
	{
		if (vertexShaderPath != "null")
		{
			std::ifstream vertexfile(vertexShaderPath);
			while (getline(vertexfile, line))
			{
				ss[0] << line << '\n';
			}

		}
		else
		{
			ss[0] << "null";
		}

	}

	{
		if (fragmentShaderPath != "null")
		{
			std::ifstream fragmentfile(fragmentShaderPath);
			while (getline(fragmentfile, line))
			{
				ss[1] << line << '\n';
			}

		}
		else
		{
			ss[1] << "null";
		}

	}
	return { ss[0].str(), ss[1].str() };
	
}


unsigned int Shader::CompileShader(unsigned int type, const std::string source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr); //之前是NULL 现在是nullptr
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile" <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< "shader!" << std::endl;
		
		std::cout << message << std::endl;
		free(message);
		glDeleteShader(id);
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs, fs;
	if (vertexShader != "null")
	{
		vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		glAttachShader(program, vs);

	}
	else
	{
		vs = 0;
	}
	if (fragmentShader != "null")
	{
		fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
		glAttachShader(program, fs);

	}
	else
	{
		fs = 0;
	}

	glLinkProgram(program);
	glValidateProgram(program);

	if (vs != 0)
	{
		glDeleteShader(vs);
	}
	if (fs != 0)
	{
		glDeleteShader(fs);
	}

	return program;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}
void Shader::SetUnifrom1iv(const std::string& name, int count, const int* value)
{
	GLCall(glUniform1iv(GetUniformLocation(name), count, value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	if (glm::value_ptr(matrix))
	{
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));

	}
	else
	{
		std::cout <<"Warning: null pointer for SetUniformMat4f" << std::endl;
	}
}



int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];
	
	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform:'" << name << "' does not exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}