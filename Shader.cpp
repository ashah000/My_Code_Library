#include "Shader.h"

Shader::Shader()
{
	shaderID = 0;
	uniformProjection = 0;
	unifromModel = 0;
}

// Entry Point for Shader Compilation, Add Shader etc.
void Shader::CreateFromString(const char* VertexCode, const char* fragmentCode)
{
	CompileShader(VertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();
	CompileShader(vertexCode, fragmentCode);

}

std::string Shader::ReadFile(const char * fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in); // Class for reading from files only. No Write.

	if (!fileStream.is_open())
	{
		printf("Failed to read %s! File doesnot exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

void Shader::CompileShader(const char* VertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();
	if (!shaderID) {
		printf("Error Creating Shader Program!\n");
		return;
	}
	AddShader(shaderID, VertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar elog[1024] = { 0 };

	//create executables on graphic card
	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(elog), NULL, elog);
		printf("Error linking Program  = '%s'\n", elog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(elog), NULL, elog);
		printf("Error Validating Program  = '%s'\n", elog);
		return;
	}

	unifromModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
}

void Shader::AddShader(GLuint theProgram, const char * shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);
	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar elog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(theShader, sizeof(elog), NULL, elog);
		printf("Error Compiling the %d Shader  = '%s'\n", shaderType, elog);
		return;
	}

	glAttachShader(theProgram, theShader);
	return;
}

GLuint Shader::GetProjectionLocation()
{
	return uniformProjection;
}

GLuint Shader::GetModelLocation()
{
	return unifromModel;
}

void Shader::UseShader()
{
	glUseProgram(shaderID);
}

void Shader::ClearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
	uniformProjection = 0;
	unifromModel = 0;
}

Shader::~Shader()
{
	ClearShader();
}
