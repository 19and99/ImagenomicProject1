#pragma once

struct RGB {
public:
	static const int bytesPerPixel = 3;
	static const int R = 0;
	static const int G = 1;
	static const int B = 2;

};
struct BGR {
	static const int bytesPerPixel = 3;
	static const int R = 2;
	static const int G = 1;
	static const int B = 0;

};
struct RGBA {
	static const int bytesPerPixel = 3;
	static const int R = 0;
	static const int G = 1;
	static const int B = 2;
	static const int A = 3;
};
struct BGRA {
	static const int bytesPerPixel = 3;
	static const int R = 2;
	static const int G = 1;
	static const int B = 0;
	static const int A = 3;
};
