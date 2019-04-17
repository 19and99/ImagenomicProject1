#pragma once
#include "ImageFormats.h"
#include "GenericImage.h"
template <class T>
class Image : public GenericImage
{

public:
	Image();
	Image(Bitmap* bmp_) :
		GenericImage(bmp_)
	{}
	~Image();

	int GetHeight() { return height; }
	int GetWidth() { return width; }
	unsigned int GetPixel(int xPos, int yPos) {
		int r = T::R;
		int g = T::G;
		int b = T::B;

		int bpp = (T::bytesPerPixel * 8);
		u_int ret = 0;


		char* charTmp = (char*)data.Scan0;
		charTmp += yPos * stride + (xPos * bpp / 8);
		unsigned char a = 0, b = 0, c = 0, d = 0;
		if (bpp == 24) {
			a = charTmp[r];
			b = charTmp[g];
			c = charTmp[b];
			ret += a;
			ret = ret << 8;
			ret += b;
			ret = ret << 8;
			ret += c;
			ret = ret << 8;
		}
		else if (bpp == 32) {
			int alpha = T::A;
			a = charTmp[r];
			b = charTmp[g];
			c = charTmp[b];
			d = charTmp[alpha];
			ret += a;
			ret = ret << 8;
			ret += b;
			ret = ret << 8;
			ret += c;
			ret << 8;
			ret += d;
		}

		return ret;
	}
	void SetPixel(int xPos, int yPos, unsigned int value) {
		int r = T::R;
		int g = T::G;
		int b = T::B;

		int bpp = T::bytesPerPixel;
		unsigned char a = 0, b = 0, c = 0, d = 0;
		a = value >> 24;
		b = value >> 16;
		c = value >> 8;
		d = value;

		char* charTmp = (char*)data.Scan0;
		charTmp += yPos * stride + (xPos * bpp / 8);

		if (bpp == 24) {
			charTmp[r] = a;
			charTmp[g] = b;
			charTmp[b] = c;
		}
		else if (bpp == 32) {
			int alpha = T::A;
			charTmp[r] = a;
			charTmp[g] = b;
			charTmp[b] = c;
			charTmp[alpha] = d;
		}
	}
	void* GetData() { return data.Scan0; }
	int GetStride() { return stride; }

	void Unlock() {
		bmp->UnlockBits(&data);
	}
};

