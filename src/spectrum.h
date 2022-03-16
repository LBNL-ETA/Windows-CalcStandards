#ifndef WINDOW_STANDARDS_SPECTRUM_H_
#define WINDOW_STANDARDS_SPECTRUM_H_

#include <string>
#include <vector>
#include <limits>
namespace window_standards
{
    enum class Spectrum_Type
    {
        NONE,
        FILE,
        BLACKBODY,
        UV_ACTION,
        KROCHMANN
    };

    struct Spectrum
    {
        Spectrum_Type type;
        std::string description;
        double t = std::numeric_limits<double>::quiet_NaN();
        double a = std::numeric_limits<double>::quiet_NaN();
        double b = std::numeric_limits<double>::quiet_NaN();
        std::vector<std::pair<double, double>> values;
    };
}   // namespace window_standards
#endif
