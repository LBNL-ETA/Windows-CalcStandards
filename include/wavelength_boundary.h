#ifndef WINDOWS_STANDARDS_WAVELENGTH_BOUNDARY_H_
#define WINDOWS_STANDARDS_WAVELENGTH_BOUNDARY_H_

#include <limits>

enum class Wavelength_Boundary_Type
{
	NUMBER,
	WAVELENGTH_SET
};

struct Wavelength_Boundary
{
	Wavelength_Boundary_Type type;
	double value = std::numeric_limits<double>::quiet_NaN();
};

#endif
