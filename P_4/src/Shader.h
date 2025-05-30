#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;

};

class Shader
{
private:
	//std::string m_FilePath;
	std::string m_VertexPath;
	std::string m_FragmentPath;
	unsigned int m_RendererID;

	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& vertPath, const std::string& fragPath);
	Shader(const std::string& vertPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value); //texture
	void SetUnifrom1iv(const std::string& name, int count, const int* values); //textureunit
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	
private:
	//ShaderProgramSource ParseShader(const std::string& filepath);
	ShaderProgramSource ParseShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	unsigned int CompileShader(unsigned int type, const std::string source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name);
};