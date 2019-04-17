#pragma once

#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

using namespace Gdiplus;
class GenericImage
{
protected:
	Bitmap* bmp;
	int height;
	int width;
	int stride;
	BitmapData data;
public:
	GenericImage(Bitmap* bmp_);
	GenericImage();

	int GetHeight() { return height; }
	int GetWidth() { return width; }
	unsigned int GetPixel(int xPos, int yPos);
	void SetPixel(int xPos, int yPos, u_int value);


	void* GetData() { return data.Scan0; }
	int GetStride() { return stride; }

	void Unlock();
};

