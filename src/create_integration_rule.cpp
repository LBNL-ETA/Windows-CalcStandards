#include "create_integration_rule.h"

#include <regex>

Integration_Rule create_integration_rule(std::string const& line)
{
	Integration_Rule integration_rule;

	if(line.find("Trapezoidal") != std::string::npos)
	{
		integration_rule.type = Integration_Rule_Type::TRAPEZOIDAL;
        integration_rule.k = 1;
	}
	else if(line.find("Rectangular") != std::string::npos)
	{
		integration_rule.type = Integration_Rule_Type::RECTANGULAR;
        integration_rule.k = 1;
	}
	else if(line.find("Table") != std::string::npos)
	{
		integration_rule.type = Integration_Rule_Type::TABLE;
        integration_rule.k = 1;
	}

	std::regex pattern(".*k=(\\S+)\\).*");
	std::smatch matches;
	if(std::regex_search(line, matches, pattern))
	{
		std::string k = matches[1].str();
		integration_rule.k = std::stod(k);
	}
	return integration_rule;
}