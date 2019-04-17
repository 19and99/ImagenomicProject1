#pragma once
#include "GenericFilter.h"
class BoxBlur :
	public GenericFilter
{
private:
	int radius;
public:
	virtual void filter();
	BoxBlur();
	BoxBlur(GenericImage*,int);
	~BoxBlur();
	void horizontalBlur();
	void verticalBlur();
};

