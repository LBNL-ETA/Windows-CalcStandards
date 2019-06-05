#include <fstream>
#include <regex>

#include "create_wavelength_set.h"
#include "util.h"

Wavelength_Set load_wavelength_set(std::istream & input)
{
	std::string line;
	Wavelength_Set wavelength_set;
	double multiplier = 1.0;

	wavelength_set.type = Wavelength_Set_Type::FILE;

	while(std::getline(input, line))
	{
		std::string line_lower = to_lower(line);
		if(line_lower.find("description") != std::string::npos)
		{
			std::string description = line.substr(line.find(":") + 2);
			wavelength_set.description = description;
			continue;
		}
		if(line_lower.find("wavelength units") != std::string::npos)
		{
			if(line_lower.find("nanometer") != std::string::npos)
			{
				multiplier *= .001;				
			}
			continue;
		}

		std::regex pattern("\\s*(\\S+)\\s*");
		std::smatch matches;
		if(std::regex_search(line, matches, pattern))
		{
			std::string wl = matches[1].str();
			wavelength_set.values.push_back(std::stod(wl) * multiplier);
		}
	}

	return wavelength_set;
}

Wavelength_Set load_wavelength_set(std::string const& path)
{
	std::ifstream fin(path);
	return load_wavelength_set(fin);
}

Wavelength_Set create_wavelength_set(std::string const& line, std::string const& standard_directory)
{
	Wavelength_Set wavelength_set;

	if(line.find("Source") != std::string::npos)
	{
		wavelength_set.type = Wavelength_Set_Type::SOURCE;
		wavelength_set.description = "Source";
	}
	else if(line.find("Data") != std::string::npos)
	{
		wavelength_set.type = Wavelength_Set_Type::DATA;
		wavelength_set.description = "Data";
	}
	else
	{
		std::string wavelength_set_path = standard_directory;
		wavelength_set_path += line;
		wavelength_set = load_wavelength_set(wavelength_set_path);
	}

	return wavelength_set;
}