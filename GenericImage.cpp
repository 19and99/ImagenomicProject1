#include "stdafx.h"
#include "GenericImage.h"


GenericImage::GenericImage(Bitmap* bmp_)
{
	bmp = bmp_;
	Rect rect(0, 0, (*bmp).GetWidth(), (*bmp).GetHeight());
	(*bmp).LockBits(&rect, ImageLockModeWrite, (*bmp).GetPixelFormat(), &data);


	width = data.Width;
	height = data.Height;
	stride = data.Stride;

}

GenericImage::GenericImage()
	:data()
{
	width = 0;
	height = 0;
	stride = 0;
}



u_int GenericImage::GetPixel(int xPos, int yPos) {
	PixelFormat format;
	format = bmp->GetPixelFormat();
	int bpp = Gdiplus::GetPixelFormatSize(format);
	u_int ret = 0;


	char* charTmp = (char*)data.Scan0;
	charTmp += yPos * stride + (xPos * bpp / 8);
	unsigned char a = 0, b = 0, c = 0,d = 0;
	if(bpp == 24){
		a = charTmp[0];
		b = charTmp[1];
		c = charTmp[2];
		ret += a;
		ret = ret << 8;
		ret += b;
		ret = ret << 8;
		ret += c;
		ret = ret << 8;
	}
	else if(bpp == 32) {
		a = charTmp[0];
		b = charTmp[1];
		c = charTmp[2];
		d = charTmp[3];
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



void GenericImage::SetPixel(int xPos, int yPos, u_int value) {
	PixelFormat format;
	format = bmp->GetPixelFormat();
	int bpp = Gdiplus::GetPixelFormatSize(format);
	unsigned char a = 0, b = 0, c = 0, d = 0;
	a = value >> 24;
	b = value >> 16;
	c = value >> 8;
	d = value;

	char* charTmp = (char*)data.Scan0;
	charTmp += yPos * stride + (xPos * bpp / 8);

	if (bpp == 24) {
		charTmp[0] = a;
		charTmp[1] = b;
		charTmp[2] = c;
	}
	else if (bpp == 32) {
		charTmp[0] = a;
		charTmp[1] = b;
		charTmp[2] = c;
		charTmp[3] = d;
	}
}





void GenericImage::Unlock() {
	bmp->UnlockBits(&data);
}