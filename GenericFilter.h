#pragma once
#include "GenericImage.h"
class GenericFilter
{
protected:
	GenericImage* image;
public:
	GenericFilter();
	GenericFilter(GenericImage*);
	~GenericFilter();

	virtual void filter() = 0;
};

