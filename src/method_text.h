#ifndef WINDOWS_STANDARDS_METHOD_TEXT_H_
#define WINDOWS_STANDARDS_METHOD_TEXT_H_

#include <string>

struct Method_Text
{
	std::string name;
	std::string description;
	std::string source_spectrum;
	std::string detector_spectrum;
	std::string wavelength_set;
	std::string integration_rule;
	std::string minimum_wavelength;
	std::string maximum_wavelength;
};

#endif
