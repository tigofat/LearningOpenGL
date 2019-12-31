#pragma once


#define Assert(x) if (!(x)) { };

#define GLCall(x) GLClearError();\
    x;\
    Assert(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* functionName, const char* fileName, int line);