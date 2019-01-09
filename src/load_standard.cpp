#include <map>
#include <algorithm>
#include <functional>
#include <regex>

#include "load_standard.h"


struct Method_Text
{
	std::string name;
	std::string description;
	std::string source_spectrum;
	std::string detector_spectrum;
	std::string wavelength_set;
	std::string integration_rule;
	std::string minimum_wavelength;
	std::string maximum_wavelength;
};

Spectrum load_spectrum(std::istream const& input)
{
	Spectrum spectrum;
	double multiplier = 1.0;

	while(std::getline(input, line))
	{
		if(line.find("Description") != std::string::npos)
		{
			std::string description = line.substr(line.find(":") + 2);
			spectrum.description = description;
			continue;
		}
		if(line.find("Wavelength Units") != std::string::npos
			&& line.find("Nanometer") != std::string::npos)
		{
			multiplier *= .001;
			continue;
		}

		std::regex pattern("\s*(\S+)\s+(\S+)\s*");
		auto itr = std::sregex_iterator(line.begin(), line.end(), pattern);

		if(itr != std::sregex_iterator())
		{
			std::string wl = itr->str(1);
			std::string val = itr->str(2);
			spectrum.values.push_back(std::make_pair<double, double>(std::stod(wl) * multiplier, std::stod(val)));
		}
	}
	
	return spectrum;
}

Spectrum load_spectrum(std::string const& path)
{
	std::ifstream fin(path);
	return load_spectrum(fin);
}

Spectrum create_spectrum(std::string const& line)
{
	Spectrum spectrum;

	if(line.find("None") != std::string::npos)
	{
		spectrum.type = Spectrum_Type::NONE;
		spectrum.description = "None";
	}
	else if(line.find("Blackbody") != std::string::npos 
			&& line.find(".SSP") == std::string::npos)
	{
		spectrum.type = Spectrum_Type::BLACKBODY;
		spectrum.description = "Blackbody";

		std::regex pattern(".*T=(.*)K\)")
		auto itr = std::sregex_iterator(line.begin(), line.end(), pattern);
		std::string val = itr->str();
		spectrum.t = std::stod(val);
	}
	else if(line.find("UV Action") != std::string::npos
			&& line.find(".SSP") == std::string::npos)
	{
		spectrum.type = Spectrum_Type::UV_ACTION;
		spectrum.description = "UV Action";
		std::regex pattern(".*a=(.*), b=(.*)\)")
		auto itr = std::sregex_iterator(line.begin(), line.end(), pattern);
		std::string a = itr->str(1);
		std::string a = itr->str(2);
		spectrum.a = std::stod(a);
		spectrum.b = std::stod(b);
	}
	else if(line.find("Krochmann") != std::string::npos
			&& line.find(".SSP") == std::string::npos))
	{
		spectrum.type = Spectrum_Type::KROCHMANN;
		spectrum.description = "Krochmann";
	}
	else
	{
		spectrum = load_spectrum(line);
	}

	return spectrum;
}

Integration_Rule create_integration_rule(std::string const& line)
{
	Integration_Rule integration_rule;
	
	if(line.find("Trapezoidal") != std::string::npos)
	{
		integration_rule.type = Integration_Rule_Type::TRAPEZOIDAL;
	}
	else if(line.find("Rectangular") != std::string::npos)
	{
		integration_rule.type = Integration_Rule_Type::RECTANGULAR;
	}
	else if(line.find("Table") != std::string::npos)
	{
		integration_rule.type = Integration_Rule_Type::TABLE;
	}

	std::regex pattern(".*k=(\S+)\).*");
	auto itr = std::sregex_iterator(line.begin(), line.end(), pattern);

	if(itr != std::sregex_iterator())
	{
		std::string k = itr->str(1);
		integration_rule.k = std::stod(k);
	}

	return integration_rule;
}

Wavelength_Boundry create_wavelength_boundry(std::string const& line)
{
	Wavelength_Boundry wavelength_boundry;

	if(line.find("Wavelength set") != std::string::npos)
	{
		wavelength_boundry.type = Wavelength_Boundry_Type::WAVELENGTH_SET;
	}	
	else
	{
		wavelength_boundry.type = Wavelength_Boundry_Type::NUMBER;
		wavelength_boundry.value = std::stod(line);
	}

	return wavelength_boundry;
}

Wavelength_Set load_wavelength_set(std::istream const& input)
{
	Wavelength_Set wavelength_set;
	double multiplier = 1.0;

	while(std::getline(input, line))
	{
		if(line.find("Description") != std::string::npos)
		{
			std::string description = line.substr(line.find(":") + 2);
			wavelength_set.description = description;
			continue;
		}
		if(line.find("Wavelength Units") != std::string::npos
			&& line.find("Nanometer") != std::string::npos)
		{
			multiplier *= .001;
			continue;
		}

		std::regex pattern("\s*(\S+)\s*");
		auto itr = std::sregex_iterator(line.begin(), line.end(), pattern);

		if(itr != std::sregex_iterator())
		{
			std::string wl = std::stod(itr->str(1));
			wavelength_set.values.push_back(wl * multiplier);
		}
	}

	return wavelength_set;
}

Wavelength_Set load_wavelength_set(std::string const& path)
{
	std::ifstream fin(path);
	return load_wavelength_set(fin);
}

Wavelength_Set create_wavelength_set(std::string const& line)
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
		wavelength_set = load_wavelength_set(line);
	}

	return wavelength_set;
}

Method convert(Method_Text const& method_text)
{
	Method method;

	method.name = method_text.name;
	method.description = method_text.description;

	return method;
}

std::vector<Method> convert(std::vector<Method_Text> const& method_blocks)
{
	std::vector<Method> methods;

	for(Method_Text const& method_block : method_blocks)
	{
		methods.push_back(convert(method_block));
	}

	return methods;
}

std::string text_after_colon(std::string const& s)
{
	return s.substr(s.find(":") + 2);
}

Method_Text convet(std::vector<std::string> const& method_from_file)
{
	Method_Text converted_method;

	std::map<std::string, std::function<void(std::string const&)>> fields_to_params;
	fields_to_params["Name"] = [&converted_method](std::string const& line) {converted_method.name = text_after_colon(line); };
	fields_to_params["Description"] = [&converted_method](std::string const& line) {converted_method.description = text_after_colon(line); };
	fields_to_params["Source Spectrum"] = [&converted_method](std::string const& line) {converted_method.source_spectrum = text_after_colon(line); };
	fields_to_params["Detector Spectrum"] = [&converted_method](std::string const& line) {converted_method.detector_spectrum = text_after_colon(line); };
	fields_to_params["Wavelength Set"] = [&converted_method](std::string const& line) {converted_method.wavelength_set = text_after_colon(line); };
	fields_to_params["Integration Rule"] = [&converted_method](std::string const& line) {converted_method.integration_rule = text_after_colon(line); };
	fields_to_params["Maximum Wavelength"] = [&converted_method](std::string const& line) {converted_method.minimum_wavelength = text_after_colon(line); };
	fields_to_params["Minimum Wavelength"] = [&converted_method](std::string const& line) {converted_method.maximum_wavelength = text_after_colon(line); };

	for(std::string const& line : method_from_file)
	{
		for(std::pair<std::string, std::function<void(std::string const&)> const& kv : fields_to_params)
		{
			if(line.find(kv.first) != std::string::npos)
			{
				kv.second(line);
			}
		}
	}

	return converted_method;
}

std::vector<Method_Text> convert(std::vector<std::vector<std::string>> const& methods_from_file)
{
	std::vector<Method_Text> converted_methods;

	for(std::vector<std::string> const& method_section : methods_from_file)
	{
		converted_methods.push_back(convet(method_section));
	}

	return converted_methods;
}

Standard load_standard(std::istream const& input)
{
	std::string line;
	std::string description;
	std::string methods_provided;

	bool finished_method = false;

	std::vector<std::vector<std::string>> methods;

	while(std::getline(input, line))
	{
		if(line.find("Standard Description") != std::string::npos)
		{
			description = line.substr(line.find(":") + 2);
			continue;
		}
		if(line.find("Standard Provides Methods") != std::string::npos)
		{
			methods_provided = line.substr(line.find(":") + 2);
			continue;
		}

		if(line.find("Name") != std::string::npos)
		{
			method_text.clear();
		}

		method_text.push_back(line);

		if(line.find("Maximum Wavelength") != std::string::npos)
		{
			methods.push_back(method_text);
		}
	}

	std::vector<Method_Text> semi_converted = convert(methods);
}

Standard load_standard(std::string const& path)
{
	std::ifstream fin(path);
	return load_standard(fin);
}