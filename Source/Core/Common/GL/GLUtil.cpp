// Copyright 2008 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include "Common/Assert.h"
#include "Common/GL/GLInterfaceBase.h"
#include "Common/GL/GLUtil.h"
#include "Common/Logging/Log.h"

cInterfaceBase *GLInterface;
static GLuint attributelessVAO = 0;
static GLuint attributelessVBO = 0;

void InitInterface()
{
	GLInterface = HostGL_CreateGLInterface();
}

GLuint OpenGL_CompileProgram(const char* vertexShader, const char* fragmentShader)
{
	// generate objects
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint programID = glCreateProgram();

	// compile vertex shader
	glShaderSource(vertexShaderID, 1, &vertexShader, nullptr);
	glCompileShader(vertexShaderID);
#if defined(_DEBUG) || defined(DEBUGFAST) || defined(DEBUG_GLSL)
	GLint Result = GL_FALSE;
	char stringBuffer[1024];
	GLsizei stringBufferUsage = 0;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderInfoLog(vertexShaderID, 1024, &stringBufferUsage, stringBuffer);

	if (Result && stringBufferUsage)
	{
		ERROR_LOG(VIDEO, "GLSL vertex shader warnings:\n%s%s", stringBuffer, vertexShader);
	}
	else if (!Result)
	{
		ERROR_LOG(VIDEO, "GLSL vertex shader error:\n%s%s", stringBuffer, vertexShader);
	}
	else
	{
		DEBUG_LOG(VIDEO, "GLSL vertex shader compiled:\n%s", vertexShader);
	}

	bool shader_errors = !Result;
#endif

	// compile fragment shader
	glShaderSource(fragmentShaderID, 1, &fragmentShader, nullptr);
	glCompileShader(fragmentShaderID);
#if defined(_DEBUG) || defined(DEBUGFAST) || defined(DEBUG_GLSL)
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderInfoLog(fragmentShaderID, 1024, &stringBufferUsage, stringBuffer);

	if (Result && stringBufferUsage)
	{
		ERROR_LOG(VIDEO, "GLSL fragment shader warnings:\n%s%s", stringBuffer, fragmentShader);
	}
	else if (!Result)
	{
		ERROR_LOG(VIDEO, "GLSL fragment shader error:\n%s%s", stringBuffer, fragmentShader);
	}
	else
	{
		DEBUG_LOG(VIDEO, "GLSL fragment shader compiled:\n%s", fragmentShader);
	}

	shader_errors |= !Result;
#endif

	// link them
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
#if defined(_DEBUG) || defined(DEBUGFAST) || defined(DEBUG_GLSL)
	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
	glGetProgramInfoLog(programID, 1024, &stringBufferUsage, stringBuffer);

	if (Result && stringBufferUsage)
	{
		ERROR_LOG(VIDEO, "GLSL linker warnings:\n%s%s%s", stringBuffer, vertexShader, fragmentShader);
	}
	else if (!Result && !shader_errors)
	{
		ERROR_LOG(VIDEO, "GLSL linker error:\n%s%s%s", stringBuffer, vertexShader, fragmentShader);
	}
#endif

	// cleanup
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}

void OpenGL_CreateAttributelessVAO()
{
	glGenVertexArrays(1, &attributelessVAO);
	_dbg_assert_msg_(VIDEO, attributelessVAO != 0, "Attributeless VAO should have been created successfully.")

	// In a compatibility context, we require a valid, bound array buffer.
	glGenBuffers(1, &attributelessVBO);
	_dbg_assert_msg_(VIDEO, attributelessVBO != 0, "Attributeless VBO should have been created successfully.")

	// Initialize the buffer with nothing.  16 floats is an arbitrary size that may work around driver issues.
	glBindBuffer(GL_ARRAY_BUFFER, attributelessVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 16, nullptr, GL_STATIC_DRAW);

	// We must also define vertex attribute 0.
	glBindVertexArray(attributelessVAO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
}

void OpenGL_BindAttributelessVAO()
{
	_dbg_assert_msg_(VIDEO, attributelessVAO != 0, "Attributeless VAO should have already been created.")
	glBindVertexArray(attributelessVAO);
}

void OpenGL_DeleteAttributelessVAO()
{
	_dbg_assert_msg_(VIDEO, attributelessVAO != 0, "Attributeless VAO should have already been created.")
	if (attributelessVAO != 0)
	{
		glDeleteVertexArrays(1, &attributelessVAO);
		glDeleteBuffers(1, &attributelessVBO);

		attributelessVAO = 0;
		attributelessVBO = 0;
	}
}
