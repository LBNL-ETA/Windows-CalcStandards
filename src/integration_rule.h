#ifndef WINDOWS_STANDARDS_INTEGRATION_RULE_H_
#define WINDOWS_STANDARDS_INTEGRATION_RULE_H_

#include <limits>

enum class Integration_Rule_Type
{
	TRAPEZOIDAL,
	RECTANGULAR,
	TABLE
};

struct Integration_Rule
{
	Integration_Rule_Type type;
	double k = std::numeric_limits<double>::quiet_NaN();
};

#endif