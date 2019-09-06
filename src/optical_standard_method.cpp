#include "optical_standard_method.h"
namespace window_standards
{
    std::map<Optical_Standard_Method_Type, std::string> method_type_to_name()
    {
        std::map<Optical_Standard_Method_Type, std::string> m;
        m[Optical_Standard_Method_Type::SOLAR] = "Solar";
        m[Optical_Standard_Method_Type::PHOTOPIC] = "Photopic";
        m[Optical_Standard_Method_Type::COLOR_TRISTIMX] = "Color_TristimX";
        m[Optical_Standard_Method_Type::COLOR_TRISTIMY] = "Color_TristimY";
        m[Optical_Standard_Method_Type::COLOR_TRISTIMZ] = "Color_TristimZ";
        m[Optical_Standard_Method_Type::THERMAL_IR] = "Thermal IR";
        m[Optical_Standard_Method_Type::TUV] = "TUV";
        m[Optical_Standard_Method_Type::SPF] = "SPF";
        m[Optical_Standard_Method_Type::TDW] = "TDW";
        m[Optical_Standard_Method_Type::TKR] = "TKR";

        return m;
    }
}   // namespace window_standards
