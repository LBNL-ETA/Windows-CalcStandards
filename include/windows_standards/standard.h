#ifndef WINDOWS_STANDARDS_STANDARD_H_
#define WINDOWS_STANDARDS_STANDARD_H_

#include <vector>

#include "method.h"

struct Standard
{
	std::string name;
	std::string description;
	std::vector<Method> methods;
};

#endif