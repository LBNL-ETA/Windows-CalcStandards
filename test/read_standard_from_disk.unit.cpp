#include <memory>
#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <filesystem>

#include "load_standard.h"

#include "paths.h"

extern std::string test_dir;



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

	Standard nfrc = load_standard(nfrc_std_path);
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
	std::pair<double, double> solar_expected_last_wavelength(4.045, 6.0);
	EXPECT_EQ(solar.source_spectrum.values[0], solar_expected_first_wavelength) << "Solar source spectrum first point";
	EXPECT_EQ(solar.source_spectrum.values[120], solar_expected_first_wavelength) << "Solar source spectrum last point";
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
	std::pair<double, double> photopic_expected_first_wavelength(300, 0.0);
	std::pair<double, double> photopic_expected_last_wavelength(4.045, 6.0);
	EXPECT_EQ(photopic.source_spectrum.values[0], photopic_expected_first_wavelength) << "Photopic source spectrum first point";
	EXPECT_EQ(photopic.source_spectrum.values[120], photopic_expected_first_wavelength) << "Photopic source spectrum last point";
	EXPECT_EQ(photopic.detector_spectrum.type, Spectrum_Type::NONE) << "Photopic detector spectrum type";
	EXPECT_EQ(photopic.detector_spectrum.values.size(), 0) << "Photopic detector spectrum wavelength count";
	EXPECT_EQ(photopic.wavelength_set.type, Wavelength_Set_Type::SOURCE) << "Photopic wavelength set type";
	EXPECT_EQ(photopic.wavelength_set.values.size(), 0) << "Photopic wavelength set wavelength count";
	EXPECT_EQ(photopic.integration_rule.type, Integration_Rule_Type::TRAPEZOIDAL) << "Photopic integration rule type";
	EXPECT_EQ(photopic.integration_rule.k, 1.0) << "Photopic integration rule k";
	EXPECT_EQ(photopic.min_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "Photopic minimum wavelength type";
	EXPECT_EQ(photopic.min_wavelength.value, 0.3) << "Photopic minimum wavelength value";
	EXPECT_EQ(photopic.max_wavelength.type, Wavelength_Boundary_Type::NUMBER) << "Photopic maximum wavelength type";
	EXPECT_EQ(photopic.max_wavelength.value, 2.5) << "Photopic maximum wavelength value";

	EXPECT_EQ(tristim_x.type, Method_Type::COLOR_TRISTIMX) << "Tristim X method type";
	EXPECT_EQ(tristim_y.type, Method_Type::COLOR_TRISTIMY) << "Tristim Y method type";
	EXPECT_EQ(tristim_z.type, Method_Type::COLOR_TRISTIMZ) << "Tristim Z method type";
	EXPECT_EQ(thermal_ir.type, Method_Type::THERMAL_IR) << "Thermal IR method type";
	EXPECT_EQ(tuv.type, Method_Type::TUV) << "TUV method type";
	EXPECT_EQ(spf.type, Method_Type::SPF) << "SPF method type";
	EXPECT_EQ(tdw.type, Method_Type::TDW) << "TDW method type";
	EXPECT_EQ(tkr.type, Method_Type::TKR) << "TKR method type";

	int i;
	i = 5;
}

