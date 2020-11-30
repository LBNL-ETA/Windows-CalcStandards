#include <map>
#include <algorithm>
#include <functional>
#include <regex>
#include <fstream>
#include <sstream>

#include "load_optical_standard.h"

#include "optical_standard_method_text.h"
#include "create_integration_rule.h"
#include "create_spectrum.h"
#include "create_wavelength_boundary.h"
#include "create_wavelength_set.h"

namespace window_standards
{
    std::string path_sep(std::string const & path)
    {
        if(path.find("\\") != std::string::npos)
        {
            return "\\";
        }
        if(path.find("/") != std::string::npos)
        {
            return "/";
        }
        std::stringstream err;
        err << "Unable to determine path seperator for " << path;
        throw std::runtime_error(err.str());
    }

    std::string parent_path(std::string const & path)
    {
        std::string sep = path_sep(path);
        std::string parent = path.substr(0, path.rfind(sep) + 1);
        return parent;
    }

    Optical_Standard_Method convert(Method_Text const & method_text, std::string const & standard_directory)
    {
        Optical_Standard_Method method;

        std::map<std::string, Optical_Standard_Method_Type> string_to_type;
        string_to_type["SOLAR"] = Optical_Standard_Method_Type::SOLAR;
        string_to_type["PHOTOPIC"] = Optical_Standard_Method_Type::PHOTOPIC;
        string_to_type["COLOR_TRISTIMX"] = Optical_Standard_Method_Type::COLOR_TRISTIMX;
        string_to_type["COLOR_TRISTIMY"] = Optical_Standard_Method_Type::COLOR_TRISTIMY;
        string_to_type["COLOR_TRISTIMZ"] = Optical_Standard_Method_Type::COLOR_TRISTIMZ;
        string_to_type["THERMAL IR"] = Optical_Standard_Method_Type::THERMAL_IR;
        string_to_type["TUV"] = Optical_Standard_Method_Type::TUV;
        string_to_type["SPF"] = Optical_Standard_Method_Type::SPF;
        string_to_type["TDW"] = Optical_Standard_Method_Type::TDW;
        string_to_type["TKR"] = Optical_Standard_Method_Type::TKR;

        try
        {
            std::string trimmed_name = method_text.name.substr(0, method_text.name.find_first_of("\r\n"));
            method.type = string_to_type.at(trimmed_name);
        }
        catch(std::exception & e)
        {
            std::stringstream err_msg;
            err_msg << "Unable to convert " << method_text.name << " into a method.  Error: " << e.what();
            throw std::runtime_error(err_msg.str());
        }
        method.description = method_text.description;
        method.source_spectrum = create_spectrum(method_text.source_spectrum, standard_directory);
        method.detector_spectrum = create_spectrum(method_text.detector_spectrum, standard_directory);
        method.wavelength_set = create_wavelength_set(method_text.wavelength_set, standard_directory);
        method.integration_rule = create_integration_rule(method_text.integration_rule);
        method.min_wavelength = create_wavelength_boundary(method_text.minimum_wavelength);
        method.max_wavelength = create_wavelength_boundary(method_text.maximum_wavelength);

        return method;
    }

    std::vector<Optical_Standard_Method> convert(std::vector<Method_Text> const & method_blocks, std::string const & standard_directory)
    {
        std::vector<Optical_Standard_Method> methods;

        for(Method_Text const & method_block : method_blocks)
        {
            methods.push_back(convert(method_block, standard_directory));
        }

        return methods;
    }

    std::string text_after_colon(std::string const & s)
    {
        return s.substr(s.find(":") + 2);
    }

    Method_Text convet(std::vector<std::string> const & method_from_file)
    {
        Method_Text converted_method;

        std::map<std::string, std::function<void(std::string const &)>> fields_to_params;
        fields_to_params["Name"] = [&converted_method](std::string const & line) { converted_method.name = text_after_colon(line); };
        fields_to_params["Description"] = [&converted_method](std::string const & line) { converted_method.description = text_after_colon(line); };
        fields_to_params["Source Spectrum"] = [&converted_method](std::string const & line) {
            converted_method.source_spectrum = text_after_colon(line);
        };
        fields_to_params["Detector Spectrum"] = [&converted_method](std::string const & line) {
            converted_method.detector_spectrum = text_after_colon(line);
        };
        fields_to_params["Wavelength Set"] = [&converted_method](std::string const & line) {
            converted_method.wavelength_set = text_after_colon(line);
        };
        fields_to_params["Integration Rule"] = [&converted_method](std::string const & line) {
            converted_method.integration_rule = text_after_colon(line);
        };
        fields_to_params["Minimum Wavelength"] = [&converted_method](std::string const & line) {
            converted_method.minimum_wavelength = text_after_colon(line);
        };
        fields_to_params["Maximum Wavelength"] = [&converted_method](std::string const & line) {
            converted_method.maximum_wavelength = text_after_colon(line);
        };

        for(std::string const & line : method_from_file)
        {
            for(std::map<std::string, std::function<void(std::string const &)>>::const_iterator kv = fields_to_params.begin();
                kv != fields_to_params.end();
                ++kv)
            {
                if(line.find(kv->first) != std::string::npos)
                {
                    kv->second(line);
                }
            }
        }

        return converted_method;
    }

    std::vector<Method_Text> convert(std::vector<std::vector<std::string>> const & methods_from_file)
    {
        std::vector<Method_Text> converted_methods;

        for(std::vector<std::string> const & method_section : methods_from_file)
        {
            converted_methods.push_back(convet(method_section));
        }

        return converted_methods;
    }

    std::string get_file_name(std::string const & path)
    {
        std::string fname = path.substr(path.find_last_of("\\/") + 1);
        return fname;
    }

    Optical_Standard load_optical_standard(std::string const & path)
    {
        std::string line;
        std::string description;
        std::string methods_provided;

        std::vector<std::vector<std::string>> method_blocks;
        std::vector<std::string> method_block;

        Optical_Standard standard;
        standard.file = path;
        standard.name = get_file_name(path);

        std::ifstream input(path);

        while(std::getline(input, line))
        {
            if(line.find("Standard Description") != std::string::npos)
            {
                standard.description = line.substr(line.find(":") + 2);
                continue;
            }
#if 0
		if(line.find("Standard Provides Methods") != std::string::npos)
		{
			standard.methods_provided = line.substr(line.find(":") + 2);
			continue;
		}
#endif

            if(line.find("Name") != std::string::npos)
            {
                method_block.clear();
            }

            method_block.push_back(line);

            if(line.find("Maximum Wavelength") != std::string::npos)
            {
                method_blocks.push_back(method_block);
            }
        }

        std::vector<Method_Text> method_text_blocks = convert(method_blocks);
        std::vector<Optical_Standard_Method> methods = convert(method_text_blocks, parent_path(path));
        for(Optical_Standard_Method const & method : methods)
        {
            standard.methods[method.type] = method;
        }

        return standard;
    }
}   // namespace window_standards
