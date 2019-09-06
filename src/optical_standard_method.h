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
    enum class Optical_Standard_Method_Type
    {
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

    std::map<Optical_Standard_Method_Type, std::string> method_type_to_name();

    struct Optical_Standard_Method
    {
        Optical_Standard_Method_Type type;
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
