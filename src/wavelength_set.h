#ifndef WINDOW_STANDARDS_WAVELENGTH_SET_H_
#define WINDOW_STANDARDS_WAVELENGTH_SET_H_

#include <string>
#include <vector>
namespace window_standards
{
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
}   // namespace window_standards
#endif
