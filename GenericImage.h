#pragma once

#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

using namespace Gdiplus;
class pixel {
public:
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
	pixel() {
		a = b = c = d = 0;
	}
};
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
	pixel GetPixel(int xPos, int yPos);
	void SetPixel(int xPos, int yPos, pixel value);


	void* GetData() { return data.Scan0; }
	int GetStride() { return stride; }

	void Unlock();
};

