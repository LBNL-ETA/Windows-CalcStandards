#ifndef WINDOWS_STANDARDS_STANDARD_H_
#define WINDOWS_STANDARDS_STANDARD_H_

#include <map>

#include "method.h"

struct Standard
{
	std::string name;
	std::string description;
	std::string file;
	std::map<Method_Type, Method> methods;
};

#endif