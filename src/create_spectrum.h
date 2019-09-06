#ifndef WINDOW_STANDARDS_CREATE_SPECTRUM_H_
#define WINDOW_STANDARDS_CREATE_SPECTRUM_H_

#include <string>

#include "spectrum.h"
namespace window_standards
{
	Spectrum load_spectrum(std::istream & input);
	Spectrum create_spectrum(std::string const& line, std::string const& standard_directory);
}
#endif
