#ifndef WINDOWS_STANDARDS_CREATE_SPECTRUM_H_
#define WINDOWS_STANDARDS_CREATE_SPECTRUM_H_

#include <string>

#include "spectrum.h"

Spectrum load_spectrum(std::istream & input);
Spectrum create_spectrum(std::string const& line);

#endif
