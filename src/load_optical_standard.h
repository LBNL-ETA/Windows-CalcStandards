#ifndef WINDOW_STANDARDS_LOAD_STANDARD_H_
#define WINDOW_STANDARDS_LOAD_STANDARD_H_

#include <string>

#include "optical_standard.h"
namespace window_standards
{
	Optical_Standard load_optical_standard(std::istream & in, std::string const& standard_directory);
	Optical_Standard load_optical_standard(std::string const& path);
}
#endif
