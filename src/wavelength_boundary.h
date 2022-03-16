#ifndef WINDOW_STANDARDS_WAVELENGTH_BOUNDARY_H_
#define WINDOW_STANDARDS_WAVELENGTH_BOUNDARY_H_

#include <limits>
namespace window_standards
{
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
}   // namespace window_standards
#endif
