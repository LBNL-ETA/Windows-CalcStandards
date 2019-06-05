#include <memory>
#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <filesystem>
#include <cmath>

#include "load_standard.h"

#include "paths.h"

extern std::string test_dir;

::testing::AssertionResult PAIR_NEAR(std::pair<double, double> const& a, std::pair<double, double> const& b, double delta) {
	if(std::abs(a.first - b.first) < delta && std::abs(a.second - b.second) < delta)
		return ::testing::AssertionSuccess();
	else
		return ::testing::AssertionFailure() << "Pair differs by more than " << delta;
}

class TestLoadStandardFromDisk : public testing::Test {

protected:
	virtual void SetUp() {

	}

};


TEST_F(TestLoadStandardFromDisk, TestLoadNFRC2003) {
	SCOPED_TRACE( "Begin Test: Load NFRC 2003 from disk." );
	
	std::filesystem::path nfrc_std_path(test_dir);
	nfrc_std_path /= "standards";
	nfrc_std_path /= "W5_NFRC_2003.std";

	Standard nfrc = load_standard(nfrc_std_path.string());
	EXPECT_EQ(nfrc.description, "Consistent with NFRC 300-2003 - default for WINDOW5");
	EXPECT_EQ(nfrc.methods.size(), 10) << "Number of methods loaded";
	Method solar = nfrc.methods[Method_Type::SOLAR];
	Method photopic = nfrc.methods[Method_Type::PHOTOPIC];
	Method tristim_x = nfrc.methods[Method_Type::COLOR_TRISTIMX];
	Method tristim_y = nfrc.methods[Method_Type::COLOR_TRISTIMY];
	Method tristim_z = nfrc.methods[Method_Type::COLOR_TRISTIMZ];
	Method thermal_ir = nfrc.methods[Method_Type::THERMAL_IR];
	Method tuv = nfrc.methods[Method_Type::TUV];
	Method spf = nfrc.methods[Method_Type::SPF];
	Method tdw = nfrc.methods[Method_Type::TDW];
	Method tkr = nfrc.methods[Method_Type::TKR];

	EXPECT_EQ(solar.type, Method_Type::SOLAR) << "Solar method type";
	EXPECT_EQ(solar.source_spectrum.type, Spectrum_Type::FILE) << "Solar source spectrum type";
	EXPECT_EQ(solar.source_spectrum.values.size(), 121) << "Solar source spectrum wavelength count";
	std::pair<double, double> solar_expected_first_wavelength(0.3, 0.0);
	std::pair<double, double> solar_expected_last_wavelength(4.045, 6.9);
	EXPECT_TRUE(PAIR_NEAR(solar.source_spectrum.values[0], solar_expected_first_wavelength, 1e-14)) << "Solar source spectrum first point";
	EXPECT_TRUE(PAIR_NEAR(solar.source_spectrum.values[120], solar_expected_last_wavelength, 1e-14)) << "Solar source spectrum last point";
	EXPECT_EQ(solar.detector_spectrum.type, Spectrum_Type::NONE) << "Solar detector spectrum type";
	EXPECT_EQ(solar.detector_spectrum.values.size(), 0) << "Solar detector spectrum wavelength count";
	EXPECT_EQ(solar.wavelength_set.type, Wavelength_Set_Type::SOURCE) << "Solar wavelength set type";
	EXPECT_EQ(solar.wavelength_set.values.size(), 0) << "Solar wavelength set wavelength count";
	EXPECT_EQ(solar.integration_rule.type, Integration_Rule_Type::TRAPEZOIDAL) << "Solar integration rule type";
	EXPECT_EQ(solar.integration_rule.k, 1.0) << "Solar integration rule k";
	EXPECT_EQ(solar.min_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "Solar minimum wavelength type";
	EXPECT_EQ(solar.min_wavelength.value, 0.3) << "Solar minimum wavelength value";
	EXPECT_EQ(solar.max_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "Solar maximum wavelength type";
	EXPECT_EQ(solar.max_wavelength.value, 2.5) << "Solar maximum wavelength value";

	EXPECT_EQ(photopic.type, Method_Type::PHOTOPIC) << "Photopic method type";

	EXPECT_EQ(photopic.source_spectrum.type, Spectrum_Type::FILE) << "Photopic source spectrum type";
	EXPECT_EQ(photopic.source_spectrum.values.size(), 531) << "Photopic source spectrum wavelength count";
	std::pair<double, double> photopic_source_expected_first_wavelength(0.3, 0.0341);
	std::pair<double, double> photopic_source_expected_last_wavelength(0.83, 60.3125);
	EXPECT_TRUE(PAIR_NEAR(photopic.source_spectrum.values[0], photopic_source_expected_first_wavelength, 1e-14)) << "Photopic source spectrum first point";
	EXPECT_TRUE(PAIR_NEAR(photopic.source_spectrum.values[530], photopic_source_expected_last_wavelength, 1e-14)) << "Photopic source spectrum last point";
	EXPECT_EQ(photopic.detector_spectrum.type, Spectrum_Type::FILE) << "Photopic detector spectrum type";
	EXPECT_EQ(photopic.detector_spectrum.values.size(), 81) << "Photopic detector spectrum wavelength count";
	std::pair<double, double> photopic_detector_expected_first_nonzero_wavelength(0.385, 0.0001);
	std::pair<double, double> photopic_detector_expected_last_nonzero_wavelength(0.76, 0.0001);
	EXPECT_TRUE(PAIR_NEAR(photopic.detector_spectrum.values[1], photopic_detector_expected_first_nonzero_wavelength, 1e-14)) << "Photopic detector spectrum first nonzero point";
	EXPECT_TRUE(PAIR_NEAR(photopic.detector_spectrum.values[76], photopic_detector_expected_last_nonzero_wavelength, 1e-14)) << "Photopic detector spectrum last nonzero point";
	EXPECT_EQ(photopic.wavelength_set.type, Wavelength_Set_Type::FILE) << "Photopic wavelength set type";
	EXPECT_EQ(photopic.wavelength_set.values.size(), 81) << "Photopic wavelength set wavelength count";
	EXPECT_EQ(photopic.wavelength_set.values[0], 0.38) << "Photopic wavelength set first point";
	EXPECT_EQ(photopic.wavelength_set.values[80], 0.78) << "Photopic wavelength set last point";
	EXPECT_EQ(photopic.integration_rule.type, Integration_Rule_Type::TRAPEZOIDAL) << "Photopic integration rule type";
	EXPECT_EQ(photopic.integration_rule.k, 1.0) << "Photopic integration rule k";
	EXPECT_EQ(photopic.min_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "Photopic minimum wavelength type";
	EXPECT_EQ(photopic.min_wavelength.value, 0.38) << "Photopic minimum wavelength value";
	EXPECT_EQ(photopic.max_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "Photopic maximum wavelength type";
	EXPECT_EQ(photopic.max_wavelength.value, 0.78) << "Photopic maximum wavelength value";

	EXPECT_EQ(tristim_x.type, Method_Type::COLOR_TRISTIMX) << "Tristim X method type";
	EXPECT_EQ(tristim_x.source_spectrum.type, Spectrum_Type::FILE) << "Tristim X source spectrum type";
	EXPECT_EQ(tristim_x.source_spectrum.values.size(), 531) << "Tristim_x source spectrum wavelength count";
	std::pair<double, double> tristim_x_source_expected_first_wavelength(0.3, 0.0341);
	std::pair<double, double> tristim_x_source_expected_last_wavelength(0.83, 60.3125);
	EXPECT_TRUE(PAIR_NEAR(tristim_x.source_spectrum.values[0], tristim_x_source_expected_first_wavelength, 1e-14)) << "Tristim_x source spectrum first point";
	EXPECT_TRUE(PAIR_NEAR(tristim_x.source_spectrum.values[530], tristim_x_source_expected_last_wavelength, 1e-14)) << "Tristim_x source spectrum last point";
	EXPECT_EQ(tristim_x.detector_spectrum.type, Spectrum_Type::FILE) << "Tristim_x detector spectrum type";
	EXPECT_EQ(tristim_x.detector_spectrum.values.size(), 81) << "Tristim_x detector spectrum wavelength count";
	std::pair<double, double> tristim_x_detector_expected_first_nonzero_wavelength(0.38, 0.0002);
	std::pair<double, double> tristim_x_detector_expected_last_nonzero_wavelength(0.77, 0.0001);
	EXPECT_TRUE(PAIR_NEAR(tristim_x.detector_spectrum.values[0], tristim_x_detector_expected_first_nonzero_wavelength, 1e-14)) << "Tristim_x detector spectrum first nonzero point";
	EXPECT_TRUE(PAIR_NEAR(tristim_x.detector_spectrum.values[78], tristim_x_detector_expected_last_nonzero_wavelength, 1e-14)) << "Tristim_x detector spectrum last nonzero point";
	EXPECT_EQ(tristim_x.wavelength_set.type, Wavelength_Set_Type::FILE) << "Tristim_x wavelength set type";
	EXPECT_EQ(tristim_x.wavelength_set.values.size(), 81) << "Tristim_x wavelength set wavelength count";
	EXPECT_EQ(tristim_x.wavelength_set.values[0], 0.38) << "Tristim_x wavelength set first point";
	EXPECT_EQ(tristim_x.wavelength_set.values[80], 0.78) << "Tristim_x wavelength set last point";
	EXPECT_EQ(tristim_x.integration_rule.type, Integration_Rule_Type::TRAPEZOIDAL) << "Tristim_x integration rule type";
	EXPECT_EQ(tristim_x.integration_rule.k, 1.0) << "Tristim_x integration rule k";
	EXPECT_EQ(tristim_x.min_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "Tristim_x minimum wavelength type";
	EXPECT_EQ(tristim_x.min_wavelength.value, 0.38) << "Tristim_x minimum wavelength value";
	EXPECT_EQ(tristim_x.max_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "Tristim_x maximum wavelength type";
	EXPECT_EQ(tristim_x.max_wavelength.value, 0.78) << "Tristim_x maximum wavelength value";

	EXPECT_EQ(tristim_y.type, Method_Type::COLOR_TRISTIMY) << "Tristim Y method type";
	EXPECT_EQ(tristim_y.source_spectrum.type, Spectrum_Type::FILE) << "Tristim Y source spectrum type";
	EXPECT_EQ(tristim_y.source_spectrum.values.size(), 531) << "Tristim_y source spectrum wavelength count";
	std::pair<double, double> tristim_y_source_expected_first_wavelength(0.3, 0.0341);
	std::pair<double, double> tristim_y_source_expected_last_wavelength(0.83, 60.3125);
	EXPECT_TRUE(PAIR_NEAR(tristim_y.source_spectrum.values[0], tristim_y_source_expected_first_wavelength, 1e-14)) << "Tristim_y source spectrum first point";
	EXPECT_TRUE(PAIR_NEAR(tristim_y.source_spectrum.values[530], tristim_y_source_expected_last_wavelength, 1e-14)) << "Tristim_y source spectrum last point";
	EXPECT_EQ(tristim_y.detector_spectrum.type, Spectrum_Type::FILE) << "Tristim_y detector spectrum type";
	EXPECT_EQ(tristim_y.detector_spectrum.values.size(), 81) << "Tristim_y detector spectrum wavelength count";
	std::pair<double, double> tristim_y_detector_expected_first_nonzero_wavelength(0.385, 0.0001);
	std::pair<double, double> tristim_y_detector_expected_last_nonzero_wavelength(0.755, 0.0001);
	EXPECT_TRUE(PAIR_NEAR(tristim_y.detector_spectrum.values[1], tristim_y_detector_expected_first_nonzero_wavelength, 1e-14)) << "Tristim_y detector spectrum first nonzero point";
	EXPECT_TRUE(PAIR_NEAR(tristim_y.detector_spectrum.values[75], tristim_y_detector_expected_last_nonzero_wavelength, 1e-14)) << "Tristim_y detector spectrum last nonzero point";
	EXPECT_EQ(tristim_y.wavelength_set.type, Wavelength_Set_Type::FILE) << "Tristim_y wavelength set type";
	EXPECT_EQ(tristim_y.wavelength_set.values.size(), 81) << "Tristim_y wavelength set wavelength count";
	EXPECT_EQ(tristim_y.wavelength_set.values[0], 0.38) << "Tristim_y wavelength set first point";
	EXPECT_EQ(tristim_y.wavelength_set.values[80], 0.78) << "Tristim_y wavelength set last point";
	EXPECT_EQ(tristim_y.integration_rule.type, Integration_Rule_Type::TRAPEZOIDAL) << "Tristim_y integration rule type";
	EXPECT_EQ(tristim_y.integration_rule.k, 1.0) << "Tristim_y integration rule k";
	EXPECT_EQ(tristim_y.min_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "Tristim_y minimum wavelength type";
	EXPECT_EQ(tristim_y.min_wavelength.value, 0.38) << "Tristim_y minimum wavelength value";
	EXPECT_EQ(tristim_y.max_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "Tristim_y maximum wavelength type";
	EXPECT_EQ(tristim_y.max_wavelength.value, 0.78) << "Tristim_y maximum wavelength value";

	EXPECT_EQ(tristim_z.type, Method_Type::COLOR_TRISTIMZ) << "Tristim Z method type";
	EXPECT_EQ(tristim_z.source_spectrum.type, Spectrum_Type::FILE) << "Tristim Z source spectrum type";
	EXPECT_EQ(tristim_z.source_spectrum.values.size(), 531) << "Tristim_z source spectrum wavelength count";
	std::pair<double, double> tristim_z_source_expected_first_wavelength(0.3, 0.0341);
	std::pair<double, double> tristim_z_source_expected_last_wavelength(0.83, 60.3125);
	EXPECT_TRUE(PAIR_NEAR(tristim_z.source_spectrum.values[0], tristim_z_source_expected_first_wavelength, 1e-14)) << "Tristim_z source spectrum first point";
	EXPECT_TRUE(PAIR_NEAR(tristim_z.source_spectrum.values[530], tristim_z_source_expected_last_wavelength, 1e-14)) << "Tristim_z source spectrum last point";
	EXPECT_EQ(tristim_z.detector_spectrum.type, Spectrum_Type::FILE) << "Tristim_z detector spectrum type";
	EXPECT_EQ(tristim_z.detector_spectrum.values.size(), 81) << "Tristim_z detector spectrum wavelength count";
	std::pair<double, double> tristim_z_detector_expected_first_nonzero_wavelength(0.38, 0.0007);
	std::pair<double, double> tristim_z_detector_expected_last_nonzero_wavelength(0.555, 0.0011);
	EXPECT_TRUE(PAIR_NEAR(tristim_z.detector_spectrum.values[0], tristim_z_detector_expected_first_nonzero_wavelength, 1e-14)) << "Tristim_z detector spectrum first nonzero point";
	EXPECT_TRUE(PAIR_NEAR(tristim_z.detector_spectrum.values[35], tristim_z_detector_expected_last_nonzero_wavelength, 1e-14)) << "Tristim_z detector spectrum last nonzero point";
	EXPECT_EQ(tristim_z.wavelength_set.type, Wavelength_Set_Type::FILE) << "Tristim_z wavelength set type";
	EXPECT_EQ(tristim_z.wavelength_set.values.size(), 81) << "Tristim_z wavelength set wavelength count";
	EXPECT_EQ(tristim_z.wavelength_set.values[0], 0.38) << "Tristim_z wavelength set first point";
	EXPECT_EQ(tristim_z.wavelength_set.values[80], 0.78) << "Tristim_z wavelength set last point";
	EXPECT_EQ(tristim_z.integration_rule.type, Integration_Rule_Type::TRAPEZOIDAL) << "Tristim_z integration rule type";
	EXPECT_EQ(tristim_z.integration_rule.k, 1.0) << "Tristim_z integration rule k";
	EXPECT_EQ(tristim_z.min_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "Tristim_z minimum wavelength type";
	EXPECT_EQ(tristim_z.min_wavelength.value, 0.38) << "Tristim_z minimum wavelength value";
	EXPECT_EQ(tristim_z.max_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "Tristim_z maximum wavelength type";
	EXPECT_EQ(tristim_z.max_wavelength.value, 0.78) << "Tristim_z maximum wavelength value";

	EXPECT_EQ(thermal_ir.type, Method_Type::THERMAL_IR) << "Thermal IR method type";
	EXPECT_EQ(thermal_ir.source_spectrum.type, Spectrum_Type::BLACKBODY) << "Thermal_IR source spectrum type";
	EXPECT_EQ(thermal_ir.source_spectrum.values.size(), 0) << "Thermal_IR source spectrum wavelength count";	
	EXPECT_EQ(thermal_ir.source_spectrum.t, 300) << "Thermal_IR source spectrum t";
	EXPECT_EQ(thermal_ir.detector_spectrum.type, Spectrum_Type::NONE) << "Thermal_IR detector spectrum type";
	EXPECT_EQ(thermal_ir.detector_spectrum.values.size(), 0) << "Thermal_IR detector spectrum wavelength count";
	EXPECT_EQ(thermal_ir.wavelength_set.type, Wavelength_Set_Type::DATA) << "Thermal_IR wavelength set type";
	EXPECT_EQ(thermal_ir.wavelength_set.values.size(), 0) << "Thermal_IR wavelength set wavelength count";
	EXPECT_EQ(thermal_ir.integration_rule.type, Integration_Rule_Type::TRAPEZOIDAL) << "Thermal_IR integration rule type";
	EXPECT_EQ(thermal_ir.integration_rule.k, 1.0) << "Thermal_IR integration rule k";
	EXPECT_EQ(thermal_ir.min_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "Thermal_IR minimum wavelength type";
	EXPECT_EQ(thermal_ir.min_wavelength.value, 5.0) << "Thermal_IR minimum wavelength value";
	EXPECT_EQ(thermal_ir.max_wavelength.type, Wavelength_Boundary_Type::WAVELENGTH_SET) << "Thermal_IR maximum wavelength type";

	EXPECT_EQ(tuv.type, Method_Type::TUV) << "TUV method type";
	EXPECT_EQ(tuv.source_spectrum.type, Spectrum_Type::FILE) << "TUV source spectrum type";
	EXPECT_EQ(tuv.source_spectrum.values.size(), 121) << "TUV source spectrum wavelength count";
	std::pair<double, double> tuv_source_expected_first_wavelength(0.3, 0.0);
	std::pair<double, double> tuv_source_expected_last_wavelength(4.045, 6.9);
	EXPECT_TRUE(PAIR_NEAR(tuv.source_spectrum.values[0], tuv_source_expected_first_wavelength, 1e-14)) << "TUV source spectrum first point";
	EXPECT_TRUE(PAIR_NEAR(tuv.source_spectrum.values[120], tuv_source_expected_last_wavelength, 1e-14)) << "TUV source spectrum last point";
	EXPECT_EQ(tuv.detector_spectrum.type, Spectrum_Type::NONE) << "TUV detector spectrum type";
	EXPECT_EQ(tuv.wavelength_set.type, Wavelength_Set_Type::SOURCE) << "TUV wavelength set type";
	EXPECT_EQ(tuv.wavelength_set.values.size(), 0) << "TUV wavelength set wavelength count";
	EXPECT_EQ(tuv.integration_rule.type, Integration_Rule_Type::TRAPEZOIDAL) << "TUV integration rule type";
	EXPECT_EQ(tuv.integration_rule.k, 1.0) << "TUV integration rule k";
	EXPECT_EQ(tuv.min_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "TUV minimum wavelength type";
	EXPECT_EQ(tuv.min_wavelength.value, 0.31) << "TUV minimum wavelength value";
	EXPECT_EQ(tuv.max_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "TUV maximum wavelength type";
	EXPECT_EQ(tuv.max_wavelength.value, 0.38) << "TUV maximum wavelength value";

	EXPECT_EQ(spf.type, Method_Type::SPF) << "SPF method type";
	EXPECT_EQ(spf.source_spectrum.type, Spectrum_Type::FILE) << "SPF source spectrum type";
	EXPECT_EQ(spf.source_spectrum.values.size(), 61) << "SPF source spectrum wavelength count";
	std::pair<double, double> spf_source_expected_first_wavelength(0.28, 4.12e-11);
	std::pair<double, double> spf_source_expected_last_wavelength(0.4, 0.000101);
	EXPECT_TRUE(PAIR_NEAR(spf.source_spectrum.values[0], spf_source_expected_first_wavelength, 1e-14)) << "SPF source spectrum first point";
	EXPECT_TRUE(PAIR_NEAR(spf.source_spectrum.values[60], spf_source_expected_last_wavelength, 1e-14)) << "SPF source spectrum last point";
	EXPECT_EQ(spf.detector_spectrum.type, Spectrum_Type::FILE) << "SPF detector spectrum type";
	EXPECT_EQ(spf.detector_spectrum.values.size(), 61) << "SPF detector spectrum wavelength count";
	std::pair<double, double> spf_detector_expected_first_nonzero_wavelength(0.28, 1.00);
	std::pair<double, double> spf_detector_expected_last_nonzero_wavelength(0.4, 0.000122);
	EXPECT_TRUE(PAIR_NEAR(spf.detector_spectrum.values[0], spf_detector_expected_first_nonzero_wavelength, 1e-14)) << "SPF detector spectrum first nonzero point";
	EXPECT_TRUE(PAIR_NEAR(spf.detector_spectrum.values[60], spf_detector_expected_last_nonzero_wavelength, 1e-14)) << "SPF detector spectrum last nonzero point";
	EXPECT_EQ(spf.wavelength_set.type, Wavelength_Set_Type::SOURCE) << "SPF wavelength set type";
	EXPECT_EQ(spf.wavelength_set.values.size(), 0) << "SPF wavelength set wavelength count";
	EXPECT_EQ(spf.integration_rule.type, Integration_Rule_Type::TRAPEZOIDAL) << "SPF integration rule type";
	EXPECT_EQ(spf.integration_rule.k, 1.0) << "SPF integration rule k";
	EXPECT_EQ(spf.min_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "SPF minimum wavelength type";
	EXPECT_EQ(spf.min_wavelength.value, 0.28) << "SPF minimum wavelength value";
	EXPECT_EQ(spf.max_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "SPF maximum wavelength type";
	EXPECT_EQ(spf.max_wavelength.value, 0.4) << "SPF maximum wavelength value";

	EXPECT_EQ(tdw.type, Method_Type::TDW) << "TDW method type";
	EXPECT_EQ(tdw.source_spectrum.type, Spectrum_Type::FILE) << "TDW source spectrum type";
	EXPECT_EQ(tdw.source_spectrum.values.size(), 121) << "TDW source spectrum wavelength count";
	std::pair<double, double> tdw_source_expected_first_wavelength(0.3, 0.0);
	std::pair<double, double> tdw_source_expected_last_wavelength(4.045, 6.9);
	EXPECT_TRUE(PAIR_NEAR(tdw.source_spectrum.values[0], tdw_source_expected_first_wavelength, 1e-14)) << "TDW source spectrum first point";
	EXPECT_TRUE(PAIR_NEAR(tdw.source_spectrum.values[120], tdw_source_expected_last_wavelength, 1e-14)) << "TDW source spectrum last point";
	EXPECT_EQ(tdw.detector_spectrum.type, Spectrum_Type::UV_ACTION) << "TDW detector spectrum type";
	EXPECT_EQ(tdw.detector_spectrum.values.size(), 0) << "TDW detector spectrum wavelength count";
	EXPECT_EQ(tdw.detector_spectrum.a, 3.6) << "TDW detector spectrum a";
	EXPECT_EQ(tdw.detector_spectrum.b, 12) << "TDW detector spectrum b";
	EXPECT_EQ(tdw.wavelength_set.type, Wavelength_Set_Type::SOURCE) << "TDW wavelength set type";
	EXPECT_EQ(tdw.wavelength_set.values.size(), 0) << "TDW wavelength set wavelength count";
	EXPECT_EQ(tdw.integration_rule.type, Integration_Rule_Type::TRAPEZOIDAL) << "TDW integration rule type";
	EXPECT_EQ(tdw.integration_rule.k, 1.0) << "TDW integration rule k";
	EXPECT_EQ(tdw.min_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "TDW minimum wavelength type";
	EXPECT_EQ(tdw.min_wavelength.value, 0.3) << "TDW minimum wavelength value";
	EXPECT_EQ(tdw.max_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "TDW maximum wavelength type";
	EXPECT_EQ(tdw.max_wavelength.value, 0.7) << "TDW maximum wavelength value";

	EXPECT_EQ(tkr.type, Method_Type::TKR) << "TKR method type";
	EXPECT_EQ(tkr.source_spectrum.type, Spectrum_Type::FILE) << "TKR source spectrum type";
	EXPECT_EQ(tkr.source_spectrum.values.size(), 121) << "TKR source spectrum wavelength count";
	std::pair<double, double> tkr_source_expected_first_wavelength(0.3, 0.0);
	std::pair<double, double> tkr_source_expected_last_wavelength(4.045, 6.9);
	EXPECT_TRUE(PAIR_NEAR(tkr.source_spectrum.values[0], tkr_source_expected_first_wavelength, 1e-14)) << "TKR source spectrum first point";
	EXPECT_TRUE(PAIR_NEAR(tkr.source_spectrum.values[120], tkr_source_expected_last_wavelength, 1e-14)) << "TKR source spectrum last point";
	EXPECT_EQ(tkr.detector_spectrum.type, Spectrum_Type::KROCHMANN) << "TKR detector spectrum type";
	EXPECT_EQ(tkr.detector_spectrum.values.size(), 0) << "TKR detector spectrum wavelength count";
	EXPECT_EQ(tkr.wavelength_set.type, Wavelength_Set_Type::SOURCE) << "TKR wavelength set type";
	EXPECT_EQ(tkr.wavelength_set.values.size(), 0) << "TKR wavelength set wavelength count";
	EXPECT_EQ(tkr.integration_rule.type, Integration_Rule_Type::TRAPEZOIDAL) << "TKR integration rule type";
	EXPECT_EQ(tkr.integration_rule.k, 1.0) << "TKR integration rule k";
	EXPECT_EQ(tkr.min_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "TKR minimum wavelength type";
	EXPECT_EQ(tkr.min_wavelength.value, 0.3) << "TKR minimum wavelength value";
	EXPECT_EQ(tkr.max_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "TKR maximum wavelength type";
	EXPECT_EQ(tkr.max_wavelength.value, 0.5) << "TKR maximum wavelength value";
}

TEST_F(TestLoadStandardFromDisk, TestLoadCEN) {
	SCOPED_TRACE("Begin Test: Load CEN from disk.");

	std::filesystem::path std_path(test_dir);
	std_path /= "standards";
	std_path /= "CENblackbody.std";

	Standard cen = load_standard(std_path.string());	
	EXPECT_EQ(cen.methods.size(), 7) << "Number of methods loaded";

}