#ifndef WINDOWS_STANDARDS_WAVELENGTH_SET_H_
#define WINDOWS_STANDARDS_WAVELENGTH_SET_H_

#include <string>
#include <vector>

enum class Wavelength_Set_Type
{
	FILE,
	SOURCE,
	DATA
};

struct Wavelength_Set
{
	Wavelength_Set_Type type;
	std::string description;
	std::vector<double> values;
};

#endif