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
	pixel pixel;
	unsigned char gray = 0;
	for (int i = 0; i < image->GetWidth(); ++i) {
		for (int j = 0; j < image->GetHeight(); ++j) {
			pixel = image->GetPixel(i,j);
			gray = (pixel.a + pixel.b + pixel.c) / 3;
			pixel.a = pixel.b = pixel.c = gray;
			image->SetPixel(i,j,pixel);
		}
	}
	image->Unlock();
}

BWConverter::~BWConverter()
{
}
