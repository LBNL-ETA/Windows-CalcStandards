#include <string>
#include <vector>
#include <limits>

enum class Method_Type {
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

enum class Spectrum_Type
{
	NONE,
	FILE,
	BLACKBODY,
	UV_ACTION,
	KROCHMANN
};

enum class Wavelength_Set_Type
{
	USER_FILE,
	SOURCE,
	DATA
};

enum class Integration_Rule_Type
{
	TRAPEZOIDAL,
	RECTANGULAR,
	TABLE
};

enum class Wavelength_Boundary_Type
{
	NUMBER,
	WAVELENGTH_SET
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

struct Wavelength_Set
{
	Wavelength_Set_Type type;
	std::string description;
	std::vector<double> values;
};

struct Integration_Rule
{
	Integration_Rule_Type type;
	double k = std::numeric_limits<double>::quiet_NaN();
};

struct Wavelength_Boundary
{
	Wavelength_Boundary_Type type;
	double value;
};

struct Method
{
#if 0
	Method(Method_Type const& type,
		std::string const& description,
		Spectrum const& source_spectrum,
		Spectrum const& detector_spectrum,
		Wavelength_Set const& wavelength_set,
		Integration_Rule const& integration_rule,
		Wavelength_Boundary const& min_wavelength,
		Wavelength_Boundary const& max_wavelength);

	Method();
#endif

	Method_Type type;
	std::string description;
	Spectrum source_spectrum;
	Spectrum detector_spectrum;
	Wavelength_Set wavelength_set;
	Integration_Rule integration_rule;
	Wavelength_Boundary min_wavelength;
	Wavelength_Boundary max_wavelength;
};