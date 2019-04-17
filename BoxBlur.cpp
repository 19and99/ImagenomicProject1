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
	unsigned int a = 0, b = 0, c = 0, d = 0, pixel = 0, sumA = 0, sumB = 0, sumC = 0,area = 0;
	for (int i = 0; i < image->GetWidth(); ++i) {
		for (int j = 0; j < image->GetHeight(); ++j) {
			for (int k = i - radius; k <= i + radius; ++k) {
				if (k >= 0 && k < image->GetWidth()) {
					pixel = image->GetPixel(k, j);
					a = pixel >> 24;
					b = pixel << 8;
					b = b >> 24;
					c = pixel << 16;
					c = c >> 24;
					d = pixel << 24;
					d = d >> 24;
					sumA += a;
					sumB += b;
					sumC += c;
					area++;
				}
			}
			pixel = d;

			u_int aset = sumA / area;
			u_int bset = sumB / area;
			u_int cset = sumC / area;

			pixel += 16777216 * aset + 65536 * bset + 256*cset;
			image->SetPixel(i,j,pixel);
			sumA = sumB = sumC = area = 0;
		}
	}
}

void BoxBlur::verticalBlur() {
	unsigned int a = 0, b = 0, c = 0, d = 0, pixel = 0, sumB = 0, sumC = 0, sumA = 0, area = 0;

	for (int i = 0; i < image->GetWidth(); ++i) {
		for (int j = 0; j < image->GetHeight(); ++j) {
			for (int k = j - radius; k <= j + radius; ++k) {
				if (k >= 0 && k < image->GetHeight()) {
					pixel = image->GetPixel(i, k);
					a = pixel >> 24;
					b = pixel << 8;
					b = b >> 24;
					c = pixel << 16;
					c = c >> 24;
					d = pixel << 24;
					d = d >> 24;
					sumA += a;
					sumB += b;
					sumC += c;
					area++;
				}
			}
			pixel = d;

			u_int aset = sumA / area;
			u_int bset = sumB / area;
			u_int cset = sumC / area;

			pixel += 16777216 * aset + 65536 * bset + 256 * cset;
			image->SetPixel(i, j, pixel);
			sumA = sumB = sumC = area = 0;

		}
	}
	
}

BoxBlur::~BoxBlur()
{
}
