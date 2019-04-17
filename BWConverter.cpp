#include "stdafx.h"
#include "BWConverter.h"


BWConverter::BWConverter()
{
}

BWConverter::BWConverter(GenericImage* image_)
	:GenericFilter(image_)
{
}

void BWConverter::filter() {
	unsigned int a = 0, b = 0, c = 0,d = 0,pixel = 0,gray = 0;
	for (int i = 0; i < image->GetWidth(); ++i) {
		for (int j = 0; j < image->GetHeight(); ++j) {
			pixel = image->GetPixel(i,j);
			a = pixel >> 24;
			b = pixel << 8;
			b = b >> 24;
			c = pixel << 16;
			c = c >> 24;
			d = pixel << 24;
			d = d >> 24;
			gray = (a + b + c) / 3;
			pixel = d;
			pixel += gray * 16843008;
			image->SetPixel(i,j,pixel);
		}
	}
	image->Unlock();
}

BWConverter::~BWConverter()
{
}
