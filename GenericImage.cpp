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



pixel GenericImage::GetPixel(int xPos, int yPos) {
	PixelFormat format;
	format = bmp->GetPixelFormat();
	int bpp = Gdiplus::GetPixelFormatSize(format);
	pixel ret;


	char* charTmp = (char*)data.Scan0;
	charTmp += yPos * stride + (xPos * bpp / 8);
	if(bpp == 24){
		ret.a = charTmp[0];
		ret.b = charTmp[1];
		ret.c = charTmp[2];
	}
	else if(bpp == 32) {
		ret.a = charTmp[0];
		ret.b = charTmp[1];
		ret.c = charTmp[2];
		ret.d = charTmp[3];
	}
	
	return ret;
}



void GenericImage::SetPixel(int xPos, int yPos, pixel value) {
	PixelFormat format;
	format = bmp->GetPixelFormat();
	int bpp = Gdiplus::GetPixelFormatSize(format);

	char* charTmp = (char*)data.Scan0;
	charTmp += yPos * stride + (xPos * bpp / 8);

	if (bpp == 24) {
		charTmp[0] = value.a;
		charTmp[1] = value.b;
		charTmp[2] = value.c;
	}
	else if (bpp == 32) {
		charTmp[0] = value.a;
		charTmp[1] = value.b;
		charTmp[2] = value.c;
		charTmp[3] = value.d;
	}
}





void GenericImage::Unlock() {
	bmp->UnlockBits(&data);
}