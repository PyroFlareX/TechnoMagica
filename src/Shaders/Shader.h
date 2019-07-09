#pragma once

#include "../glad/glad/glad.h"
#include "../Util/FileUtil.h"
#include <iostream>

class Shader
{
public:
	Shader(const std::string& vertPath, const std::string& fragPath)
	{
		std::string vertSource = getFileContents(vertPath);
		const char* vertPtr = vertSource.c_str();
		std::string fragSource = getFileContents(fragPath);
		const char* fragPtr = fragSource.c_str();

		//Vertex Shader
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertPtr, NULL);
		glCompileShader(vertexShader);

		//Check Success of Vert Shader
		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//Fragment Shader
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragPtr, NULL);
		glCompileShader(fragmentShader);

		//Check Success of Frag Shader
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::Fragment::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//Shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);

		//Check Success of Program
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR! Program Stuff failed!\n" << infoLog << "\n";
		}

		//Delete Shaders
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	//Use / Activate Shader
	void use()
	{
		glUseProgram(ID);
	}

	// utility uniform functions
	void setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

	//Shader Program:
	unsigned int ID;

private:
	
};