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

enum clas Wavelength_Set_Type
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
}

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

struct Wavelength_Boundry
{
	Integration_Rule_Type type;
	double value;
};

struct Method
{
	Method(Method_Type const& type,
		std::string const& description,
		Spectrum const& source_spectrum,
		Spectrum const& detector_spectrum,
		Wavelength_Set const& wavelength_set,
		Integration_Rule const& integration_rule,
		Wavelength_Boundry const& min_wavelength,
		Wavelength_Boundry const& max_wavelength);

	Method_Type type;
	std::string description;
	Spectrum source_spectrum;
	Spectrum detector_spectrum;
	Wavelength_Set wavelength_set;
	Integration_Rule integration_rule;
	Wavelength_Boundry min_wavelength;
	Wavelength_Boundry max_wavelength;
};

/*
class CalculationStandardMethod(Trackable):
	name = models.TextField(null=False, blank=False)
	calculation_standard = models.ForeignKey(CalculationStandard,
											 on_delete=models.CASCADE,
											 null=False,
											 blank=True)
	description = models.TextField(null=True, blank=True)
	source_spectrum = models.CharField(max_length=500, null=True, blank=True)
	source_spectrum_curve = models.ForeignKey(WavelengthCurve,
											  # TODO: Should we set to null instead?
											  on_delete=models.CASCADE,
											  related_name="curve_calculation_standard_methods",
											  null=True,
											  blank=True)
	detector_spectrum = models.CharField(max_length=500, null=True, blank=True)
	detector_spectrum_curve = models.ForeignKey(WavelengthCurve,
												# TODO: Should we set to null instead?
												on_delete=models.CASCADE,
												related_name="detector_calculation_standard_methods",
												null=True,
												blank=True)
	wavelength_set = models.CharField(max_length=500, null=True, blank=True)
	wavelength_set_list = models.ForeignKey(WavelengthSetList,
											# TODO: Should we set to null instead?
											on_delete=models.CASCADE,
											related_name="calculation_standard_methods",
											null=True,
											blank=True)
	integration_rule = models.CharField(max_length=500, null=True, blank=True)
	minimum_wavelength = models.CharField(max_length=100, null=True, blank=True)
	maximum_wavelength = models.CharField(max_length=100, null=True, blank=True)
*/