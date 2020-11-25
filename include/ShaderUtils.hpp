//
// Created by debyecao on 11/24/20.
//

#ifndef DRENDER_SHADERUTILS_HPP
#define DRENDER_SHADERUTILS_HPP

#include "glad/glad.h"

#include <string>

class ShaderUtils final
{
public:
	ShaderUtils();
	~ShaderUtils();

	enum class ShaderType
	{
		FRAGMENT, VERTEX
	};

	static GLuint LoadShader(std::string filepath, ShaderType type);
	static GLuint LoadShaders(std::string vertex, std::string fragment);

private:
	ShaderUtils(const ShaderUtils&) = delete;
	ShaderUtils& operator=(const ShaderUtils&) = delete;

};

#endif//DRENDER_SHADERUTILS_HPP
