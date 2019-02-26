#pragma once

struct Texture
{
	uint32_t width = 0;
	uint32_t height = 0;
	unsigned char* data = nullptr;

	~Texture()
	{
		if (data)
			delete[] data;
	}
};