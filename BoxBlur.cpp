#include "stdafx.h"
#include "BoxBlur.h"


BoxBlur::BoxBlur(GenericImage* image_,int r)
	:GenericFilter(image_),
	radius(r)
{
}

BoxBlur::BoxBlur()
{
}

void BoxBlur::filter() {
	horizontalBlur();
	verticalBlur();
	image->Unlock();
}

void BoxBlur::horizontalBlur() {
	pixel pixel;
	unsigned int sumA = 0, sumB = 0, sumC = 0;
	unsigned int length = 2 * radius + 1;
	int height = image->GetHeight();
	int width = image->GetWidth();

	for (int j = 0; j < height; ++j) {
		for (int i = 0; i < length; ++i) {
			pixel = image->GetPixel(i, j);
			sumA += pixel.a;
			sumB += pixel.b;
			sumC += pixel.c;
			if (i >= radius) {
				pixel.a = sumA / (i + 1);
				pixel.b = sumB / (i + 1);
				pixel.c = sumC / (i + 1);
				image->SetPixel(i - radius, j, pixel);
			}
		}
		for (int i = 2 * radius + 1; i < width; ++i) {
			sumA += (image->GetPixel(i, j).a - image->GetPixel(i - length, j).a);
			sumB += (image->GetPixel(i, j).b - image->GetPixel(i - length, j).b);
			sumC += (image->GetPixel(i, j).c - image->GetPixel(i - length, j).c);
			pixel.a = sumA / length;
			pixel.b = sumB / length;
			pixel.c = sumC / length;
			image->SetPixel(i - radius, j, pixel);
			}
		for (int i = width - radius; i < width; ++i) {
			int temp = i - width + radius + 1;
			sumA -= image->GetPixel(i - radius - 1, j).a;
			sumB -= image->GetPixel(i - radius - 1, j).b;
			sumC -= image->GetPixel(i - radius - 1, j).c;
			pixel.a = sumA / (length - temp);
			pixel.b = sumB / (length - temp);
			pixel.c = sumC / (length - temp);
			image->SetPixel(i, j, pixel);
		}
			sumA = sumB = sumC = 0;
	}
}

void BoxBlur::verticalBlur() {
	pixel pixel;
	unsigned int sumA = 0, sumB = 0, sumC = 0;
	unsigned int length = 2 * radius + 1;
	int height = image->GetHeight();
	int width = image->GetWidth();

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < length; ++j) {
			pixel = image->GetPixel(i, j);
			sumA += pixel.a;
			sumB += pixel.b;
			sumC += pixel.c;
			if (j >= radius) {
				pixel.a = sumA / (j + 1);
				pixel.b = sumB / (j + 1);
				pixel.c = sumC / (j + 1);
				image->SetPixel(i, j - radius, pixel);
			}
		}
		for (int j = 2 * radius + 1; j < height; ++j) {
			sumA += (image->GetPixel(i, j).a - image->GetPixel(i, j - length).a);
			sumB += (image->GetPixel(i, j).b - image->GetPixel(i, j - length).b);
			sumC += (image->GetPixel(i, j).c - image->GetPixel(i, j - length).c);
			pixel.a = sumA / length;
			pixel.b = sumB / length;
			pixel.c = sumC / length;
			image->SetPixel(i, j - radius, pixel);
		}
		for (int j = height - radius; j < height; ++j) {
			int temp = j - height + radius + 1;
			sumA -= image->GetPixel(i, j - radius - 1).a;
			sumB -= image->GetPixel(i, j - radius - 1).b;
			sumC -= image->GetPixel(i, j - radius - 1).c;
			pixel.a = sumA / (length - temp);
			pixel.b = sumB / (length - temp);
			pixel.c = sumC / (length - temp);
			image->SetPixel(i, j, pixel);
		}
		sumA = sumB = sumC = 0;
	}
}

BoxBlur::~BoxBlur()
{
}
