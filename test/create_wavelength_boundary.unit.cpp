#include <memory>
#include <gtest/gtest.h>

#include <memory>

#include "create_wavelength_boundary.h"

using namespace window_standards;

class TestCreateWavelengthBoundary : public testing::Test {

protected:
	virtual void SetUp() {

	}

};

TEST_F(TestCreateWavelengthBoundary, TestCreateWavelengthBoundary_Number) {
	SCOPED_TRACE( "Begin Test: Create Wavelength Boundary Number." );
	
	std::string line = "0.3";

	Wavelength_Boundary boundary = create_wavelength_boundary(line);
	EXPECT_EQ(boundary.type, Wavelength_Boundary_Type::NUMBER);
	EXPECT_EQ(boundary.value, 0.3);

}

TEST_F(TestCreateWavelengthBoundary, TestCreateWavelengthBoundary_Wavelength_Set) {
	SCOPED_TRACE("Begin Test: Create Wavelength Boundary Wavelength Set.");

	std::string line = "Wavelength set";

	Wavelength_Boundary boundary = create_wavelength_boundary(line);
	EXPECT_EQ(boundary.type, Wavelength_Boundary_Type::WAVELENGTH_SET);

}