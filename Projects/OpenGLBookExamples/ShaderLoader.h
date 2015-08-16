#pragma once
#define WIN32

#include "sb7.h"
#include <iostream>
#include <fstream>
#include <memory>

class ShaderFileLoader
{
public:
	static int loadShaderFile(const char* filename, GLchar** shaderSource)
	{
		std::ifstream file;
		file.open(filename, std::ios::in);
		if (!file) 
			return -1;

		long long length = getFileLength(file);

		if (length == 0)
			return -2;  // Error: Empty file.

		GLchar* array = new GLchar[(unsigned int)length + 1];
		if (*array == 0)
			return -3; // Can't reserve memory.

		// Length isn't always strlen because some characters are
		// stripped in ascii read. It is important to 0-terminate
		// the real lenght later, length is just max possible.
		
		array[length] = 0;
		unsigned int i = 0;
		while (file.good()) {
			array[i] = file.get(); // Get chars from file.
			if (!file.eof())
				i++;
		}

		array[i] = 0; // 0-terminate it at the correct position.

		*shaderSource = array;
		file.close();

		return 0; // No error.
	}

	static int unloadShader(GLchar** shaderSource)
	{
		if (*shaderSource != 0)
			delete[] * shaderSource;
		*shaderSource = 0;
		return 0;
	}

private:
	static long long getFileLength(std::ifstream& file)
	{
		if (!file.good()) return 0;
	
		std::streamoff pos = file.tellg();
		file.seekg(0, std::ios::end);
        std::streamoff length = file.tellg();
		file.seekg(std::ios::beg);

		return length;
	}
};