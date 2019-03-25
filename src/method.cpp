#include "method.h"

std::map<Method_Type, std::string> method_type_to_name()
{
	std::map<Method_Type, std::string> m;
	m[Method_Type::SOLAR] = "Solar";
	m[Method_Type::PHOTOPIC] = "Photopic";
	m[Method_Type::COLOR_TRISTIMX] = "Color_TristimX";
	m[Method_Type::COLOR_TRISTIMY] = "Color_TrisitimY";
	m[Method_Type::COLOR_TRISTIMZ] = "Color_TristimZ";
	m[Method_Type::THERMAL_IR] = "Thermal IR";
	m[Method_Type::TUV] = "TUV";
	m[Method_Type::SPF] = "SPF";
	m[Method_Type::TDW] = "TDW";
	m[Method_Type::TKR] = "TKR";

	return m;
}
