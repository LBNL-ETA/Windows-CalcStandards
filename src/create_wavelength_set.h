#ifndef WINDOWS_STANDARDS_CREATE_WAVELENGTH_SET_H_
#define WINDOWS_STANDARDS_CREATE_WAVELENGTH_SET_H_

#include <string>
#include <filesystem>

#include "wavelength_set.h"

Wavelength_Set load_wavelength_set(std::istream & input);
Wavelength_Set create_wavelength_set(std::string const& line, std::filesystem::path const& standard_directory);

#endif
