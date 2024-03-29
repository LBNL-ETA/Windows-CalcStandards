#ifndef WINDOW_STANDARDS_CREATE_WAVELENGTH_SET_H_
#define WINDOW_STANDARDS_CREATE_WAVELENGTH_SET_H_

#include <string>

#include "wavelength_set.h"
namespace window_standards
{
	Wavelength_Set load_wavelength_set(std::istream & input);
	Wavelength_Set create_wavelength_set(std::string const& line, std::string const& standard_directory);
}
#endif
