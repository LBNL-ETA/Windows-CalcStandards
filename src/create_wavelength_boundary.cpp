#include "create_wavelength_boundary.h"


Wavelength_Boundary create_wavelength_boundary(std::string const& line)
{
	Wavelength_Boundary wavelength_boundary;

	if(line.find("Wavelength set") != std::string::npos)
	{
		wavelength_boundary.type = Wavelength_Boundary_Type::WAVELENGTH_SET;
	}
	else
	{
		wavelength_boundary.type = Wavelength_Boundary_Type::NUMBER;
		wavelength_boundary.value = std::stod(line);
	}

	return wavelength_boundary;
}