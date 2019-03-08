#include <algorithm>

#include "util.h"

std::string to_lower(std::string s)
{
	/*
		This has issues with unicode but there will be many of those to deal
		with if this ever needs to really be internationalized.
		Until then this should be good enough
	*/
#pragma warning(push)
#pragma warning(disable:4244)
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
#pragma warning(pop)
	return s;
}