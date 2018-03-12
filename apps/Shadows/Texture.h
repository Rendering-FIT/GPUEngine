#pragma once

struct Texture
{
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned char* data = nullptr;

	~Texture()
	{
		if (data)
			delete[] data;
	}
};