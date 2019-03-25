#ifndef WINDOWS_STANDARDS_METHOD_H_
#define WINDOWS_STANDARDS_METHOD_H_

#include <string>
#include <map>

#include "integration_rule.h"
#include "spectrum.h"
#include "wavelength_boundary.h"
#include "wavelength_set.h"

enum class Method_Type {
	SOLAR, 
	PHOTOPIC, 
	COLOR_TRISTIMX, 
	COLOR_TRISTIMY, 
	COLOR_TRISTIMZ, 
	THERMAL_IR, 
	TUV, 
	SPF, 
	TDW, 
	TKR
};

std::map<Method_Type, std::string> method_type_to_name();

struct Method
{
	Method_Type type;
	std::string description;
	Spectrum source_spectrum;
	Spectrum detector_spectrum;
	Wavelength_Set wavelength_set;
	Integration_Rule integration_rule;
	Wavelength_Boundary min_wavelength;
	Wavelength_Boundary max_wavelength;
};

#endif
