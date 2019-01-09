#include <memory>
#include <gtest/gtest.h>

#include <memory>

#include "load_standard.h"


class TestLoadStandard : public testing::Test {

protected:
	virtual void SetUp() {

	}

};

TEST_F(TestLoadNFRC, TestLoadNFRC) {
	SCOPED_TRACE( "Begin Test: Load NFRC standard." );

	Standard nfrc = load_standard("standards/W5_NFRC_2003.std");

	EXPECT_EQ(nfrc.name, "NFRC");

}
