#ifndef WINDOW_STANDARDS_METHOD_H_
#define WINDOW_STANDARDS_METHOD_H_

#include <string>
#include <map>

#include "integration_rule.h"
#include "spectrum.h"
#include "wavelength_boundary.h"
#include "wavelength_set.h"

namespace window_standards
{
    struct Optical_Standard_Method
    {
        std::string name;
        std::string description;
        Spectrum source_spectrum;
        Spectrum detector_spectrum;
        Wavelength_Set wavelength_set;
        Integration_Rule integration_rule;
        Wavelength_Boundary min_wavelength;
        Wavelength_Boundary max_wavelength;
    };

}   // namespace window_standards
#endif
