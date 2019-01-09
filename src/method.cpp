#include "method.h"

Method::Method(Method_Type const & type, 
			std::string const & description, 
			Spectrum const & source_spectrum, 
			Spectrum const & detector_spectrum, 
			Wavelength_Set const & wavelength_set, 
			Integration_Rule const & integration_rule, 
			Wavelength_Boundry const & min_wavelength, 
			Wavelength_Boundry const & max_wavelength)
	: type(type), 
	description(description),
	source_spectrum(source_spectrum),
	detector_spectrum(detector_spectrum),
	wavelength_set(wavelength_set),
	integration_rule(integration_rule),
	min_wavelength(min_wavelength),
	max_wavelength(max_wavelength)
{
}
