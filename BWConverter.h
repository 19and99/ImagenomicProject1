#pragma once
#include "GenericFilter.h"
class BWConverter :
	public GenericFilter
{
public:
	virtual void filter();
	BWConverter();
	BWConverter(GenericImage*);
	~BWConverter();
};

