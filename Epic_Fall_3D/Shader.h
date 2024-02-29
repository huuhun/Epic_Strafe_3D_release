#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

	//active the shader
	void Use() const;

    void setBool(const std::string& shaderVarName, bool layout) const;
    void setInt(const std::string& shaderVarName, int layout) const;
    void setFloat(const std::string& shaderVarName, float layout) const;

    void setVec2(const std::string& shaderVarName, const glm::vec2& layout) const;
    void setVec2(const std::string& shaderVarName, float x, float y) const;
    void setVec3(const std::string& shaderVarName, const glm::vec3& layout) const;
    void setVec3(const std::string& shaderVarName, float x, float y, float z) const;
    void setVec4(const std::string& shaderVarName, const glm::vec4& layout) const;
    void setVec4(const std::string& shaderVarName, float x, float y, float z, float w) const;

    void setMat2(const std::string& shaderVarName, const glm::mat2& mat) const;
    void setMat3(const std::string& shaderVarName, const glm::mat3& mat) const;
    void setMat4(const std::string& shaderVarName, const glm::mat4& mat) const;

    inline unsigned int getID() const { return m_ID; }

private:
	unsigned int m_ID;
    void checkCompileErrors(GLuint shader, std::string type);
};