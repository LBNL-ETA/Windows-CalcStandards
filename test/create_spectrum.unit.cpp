#include <memory>
#include <gtest/gtest.h>

#include <memory>

#include <sstream>

#include "create_spectrum.h"

std::istringstream sample_spectrum_file()
{
	std::string contents = R"###(
	Description: ASTM E891-87 Table 1 - Direct Normal Irradiance AM1.5 - Standard Curve in Wm-2um-1 Elam direct normal spectral irradiance at lam, centered on lam and calculated using absorption data with a resolution of 20cm-1.  Identical to ISO 9845, Table 1, Column 2 AM 1.5
	Type: Source
	Wavelength Units : micron

	0.3     0
	0.305   3.4
	0.31   15.6
	0.315   41.1
	0.32   71.2
	0.325   100.2
	0.33   152.4
	0.335   155.6
	0.34   179.4
	0.345   186.7
	0.35   212
	0.36   240.5
	0.37   324
	0.38   362.4
	0.39   381.7
	0.4   556
	0.41   656.3
	0.42   690.8
	0.43   641.9
	0.44   798.5
	0.45   956.6
	0.46   990
	0.47   998
	0.48   1046.1
	0.49   1005.1
	0.5   1026.7
	0.51   1066.7
	0.52   1011.5
	0.53   1084.9
	0.54   1082.4
	0.55   1102.2
	0.57   1087.4
	0.59   1024.3
	0.61   1088.8
	0.63   1062.1
	0.65   1061.7
	0.67   1046.2
	0.69   859.2
	0.71   1002.4
	0.718   816.9
	0.7244   842.8
	0.74   971
	0.7525   956.3
	0.7575   942.2
	0.7625   524.8
	0.7675   830.7
	0.78   908.9
	0.8   873.4
	0.816   712
	0.8237   660.2
	0.8315   765.5
	0.84   799.8
	0.86   815.2
	0.88   778.3
	0.905   630.4
	0.915   565.2
	0.925   586.4
	0.93   348.1
	0.937   224.2
	0.948   271.4
	0.965   451.2
	0.98   549.7
	0.9935   630.1
	1.04   582.9
	1.07   539.7
	1.1   366.2
	1.12   98.1
	1.13   169.5
	1.137   118.7
	1.161   301.9
	1.18   406.8
	1.2   375.2
	1.235   423.6
	1.29   365.7
	1.32   223.4
	1.35   30.1
	1.395   1.4
	1.4425   51.6
	1.4625   97
	1.477   97.3
	1.497   167.1
	1.52   239.3
	1.539   248.8
	1.558   249.3
	1.578   222.3
	1.592   227.3
	1.61   210.5
	1.63   224.7
	1.646   215.9
	1.678   202.8
	1.74   158.2
	1.8   28.6
	1.86   1.8
	1.92   1.1
	1.96   19.7
	1.985   84.9
	2.005   25
	2.035   92.5
	2.065   56.3
	2.1   82.7
	2.148   76.2
	2.198   66.4
	2.27   65
	2.36   57.6
	2.45   19.8
	2.494   17
	2.537   3
	2.941   4
	2.973   7
	3.005   6
	3.056   3
	3.132   5
	3.156   18
	3.204   1.2
	3.245   3
	3.317   12
	3.344   3
	3.45   12.2
	3.573   11
	3.765   9
	4.045   6.9
	)###";

	std::istringstream f(contents);
	return f;
}

class TestCreateSpectrum : public testing::Test {

protected:
	virtual void SetUp() {

	}

};


TEST_F(TestCreateSpectrum, TestCreateSpectrum_None) {
	SCOPED_TRACE( "Begin Test: Load Spectrum None." );

	std::string line = "None";
	
	Spectrum spectrum = create_spectrum(line);

	EXPECT_EQ(spectrum.type, Spectrum_Type::NONE);
	EXPECT_EQ(spectrum.description, "None");
	std::vector<std::pair<double, double>> empty_vect;
	EXPECT_EQ(spectrum.values, empty_vect);
	
}



TEST_F(TestCreateSpectrum, TestCreateSpectrum_File) {
	SCOPED_TRACE("Begin Test: Load Spectrum From File.");

	//Not sure what the best way to test loading a file from
	//gtest using cmake is because the working directory seems to
	//depend on where the user chooses to put the cmake binaries
	//and that is outside of the control of the files.
	//
	//So in the meantime just load an example into a stringstream
	//and test the function to load from that
	std::istringstream sample_spectrum_file_contents = sample_spectrum_file();
	Spectrum spectrum = load_spectrum(sample_spectrum_file_contents);

	EXPECT_EQ(spectrum.type, Spectrum_Type::FILE);

	std::string expected_description = "ASTM E891-87 Table 1 - Direct Normal Irradiance AM1.5 - Standard Curve in Wm-2um-1 Elam direct normal spectral irradiance at lam, centered on lam and calculated using absorption data with a resolution of 20cm-1.  Identical to ISO 9845, Table 1, Column 2 AM 1.5";
	EXPECT_EQ(spectrum.description, expected_description);
	size_t expected_size = 121;
	EXPECT_EQ(spectrum.values.size(), expected_size);
	std::pair<double, double> expected_first(0.3, 0.0);
	EXPECT_EQ(spectrum.values[0], expected_first);
	std::pair<double, double> expected_last(4.045, 6.9);
	EXPECT_EQ(spectrum.values[120], expected_last);

}

TEST_F(TestCreateSpectrum, TestCreateSpectrum_Blackbody) {
	SCOPED_TRACE("Begin Test: Load Spectrum Blackbody.");

	std::string line = "Blackbody (T=300.0K)";

	Spectrum spectrum = create_spectrum(line);

	EXPECT_EQ(spectrum.type, Spectrum_Type::BLACKBODY);
	EXPECT_EQ(spectrum.description, "Blackbody");
	EXPECT_EQ(spectrum.t, 300.0);
	std::vector<std::pair<double, double>> empty_vec;
	EXPECT_EQ(spectrum.values, empty_vec);

}

TEST_F(TestCreateSpectrum, TestCreateSpectrum_UV_Action) {
	SCOPED_TRACE("Begin Test: Load Spectrum UV Action.");

	std::string line = "UV Action (a=3.6, b=12.0)";

	Spectrum spectrum = create_spectrum(line);

	EXPECT_EQ(spectrum.type, Spectrum_Type::UV_ACTION);
	EXPECT_EQ(spectrum.description, "UV Action");
	EXPECT_EQ(spectrum.a, 3.6);
	EXPECT_EQ(spectrum.b, 12.0);
	std::vector<std::pair<double, double>> empty_vec;
	EXPECT_EQ(spectrum.values, empty_vec);

}

TEST_F(TestCreateSpectrum, TestCreateSpectrum_Krochmann) {
	SCOPED_TRACE("Begin Test: Load Spectrum Krochmann.");

	std::string line = "Krochmann";

	Spectrum spectrum = create_spectrum(line);

	EXPECT_EQ(spectrum.type, Spectrum_Type::KROCHMANN);
	EXPECT_EQ(spectrum.description, "Krochmann");	
}