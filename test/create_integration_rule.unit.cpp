#include <memory>
#include <gtest/gtest.h>

#include <memory>

#include "create_integration_rule.h"

class TestCreateIntegrationRule : public testing::Test {

protected:
	virtual void SetUp() {

	}

};

TEST_F(TestCreateIntegrationRule, TestCreateIntegrationRule_Trapezoidal) {
	SCOPED_TRACE( "Begin Test: Create Trapezoidal Integration Rule." );

	std::string line = "Trapezoidal";
	Integration_Rule rule = create_integration_rule(line);

	EXPECT_EQ(rule.type, Integration_Rule_Type::TRAPEZOIDAL);

	line = "Trapezoidal (k=2.3)";
	rule = create_integration_rule(line);

	EXPECT_EQ(rule.type, Integration_Rule_Type::TRAPEZOIDAL);
	EXPECT_EQ(rule.k, 2.3);
}

TEST_F(TestCreateIntegrationRule, TestCreateIntegrationRule_Rectangular) {
	SCOPED_TRACE("Begin Test: Create Rectangular Integration Rule.");

	std::string line = "Rectangular";
	Integration_Rule rule = create_integration_rule(line);

	EXPECT_EQ(rule.type, Integration_Rule_Type::RECTANGULAR);

	line = "Rectangular (Normalized, k=1.0)";
	rule = create_integration_rule(line);

	EXPECT_EQ(rule.type, Integration_Rule_Type::RECTANGULAR);
	EXPECT_EQ(rule.k, 1.0);
}

TEST_F(TestCreateIntegrationRule, TestCreateIntegrationRule_Table) {
	SCOPED_TRACE("Begin Test: Create Table Integration Rule.");

	std::string line = "Pre-weighted Table";

	Integration_Rule rule = create_integration_rule(line);

	EXPECT_EQ(rule.type, Integration_Rule_Type::TABLE);

	line = "Pre-weighted Table (Normalized, k=1.0)";
	rule = create_integration_rule(line);

	EXPECT_EQ(rule.type, Integration_Rule_Type::TABLE);
	EXPECT_EQ(rule.k, 1.0);
}
