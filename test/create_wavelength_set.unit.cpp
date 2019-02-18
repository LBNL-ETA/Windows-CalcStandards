#include <memory>
#include <gtest/gtest.h>

#include <memory>
#include <sstream>

#include "create_wavelength_set.h"

std::istringstream sample_wavelength_set_file()
{
	std::string contents = R"###(
	Description: 5 nm intervals between 380 and 780 nm for color averages
	Wavelength Units: Nanometers
	380
	385
	390
	395
	400
	405
	410
	415
	420
	425
	430
	435
	440
	445
	450
	455
	460
	465
	470
	475
	480
	485
	490
	495
	500
	505
	510
	515
	520
	525
	530
	535
	540
	545
	550
	555
	560
	565
	570
	575
	580
	585
	590
	595
	600
	605
	610
	615
	620
	625
	630
	635
	640
	645
	650
	655
	660
	665
	670
	675
	680
	685
	690
	695
	700
	705
	710
	715
	720
	725
	730
	735
	740
	745
	750
	755
	760
	765
	770
	775
	780
	)###";

	std::istringstream f(contents);
	return f;
}

class TestCreateWavelengthSet : public testing::Test {

protected:
	virtual void SetUp() {

	}

};

TEST_F(TestCreateWavelengthSet, TestCreateWavelengthSet_File) {
	SCOPED_TRACE( "Begin Test: Create Wavelength Set From File." );

	//Not sure what the best way to test loading a file from
	//gtest using cmake is because the working directory seems to
	//depend on where the user chooses to put the cmake binaries
	//and that is outside of the control of the files.
	//
	//So in the meantime just load an example into a stringstream
	//and test the function to load from that
	std::istringstream sample_wavelength_set_file_contents = sample_wavelength_set_file();
	Wavelength_Set wl_set = load_wavelength_set(sample_wavelength_set_file_contents);

	EXPECT_EQ(wl_set.type, Wavelength_Set_Type::FILE);

	std::string expected_description = "5 nm intervals between 380 and 780 nm for color averages";
	EXPECT_EQ(wl_set.description, expected_description);
	size_t expected_size = 81;
	EXPECT_EQ(wl_set.values.size(), expected_size);	
	EXPECT_EQ(wl_set.values[0], .380);	
	EXPECT_EQ(wl_set.values[80], .780);
}

TEST_F(TestCreateWavelengthSet, TestCreateWavelengthSet_Source) {
	SCOPED_TRACE("Begin Test: Create Wavelength Set Source.");

	std::string line = "Source";

	Wavelength_Set wl_set = create_wavelength_set(line, "");

	EXPECT_EQ(wl_set.type, Wavelength_Set_Type::SOURCE);
	EXPECT_EQ(wl_set.description, "Source");
	std::vector<double> empty_vec;
	EXPECT_EQ(wl_set.values, empty_vec);
}

TEST_F(TestCreateWavelengthSet, TestCreateWavelengthSet_Data) {
	SCOPED_TRACE("Begin Test: Create Wavelength Set Data.");

	std::string line = "Data";

	Wavelength_Set wl_set = create_wavelength_set(line, "");

	EXPECT_EQ(wl_set.type, Wavelength_Set_Type::DATA);
	EXPECT_EQ(wl_set.description, "Data");
	std::vector<double> empty_vec;
	EXPECT_EQ(wl_set.values, empty_vec);
}
