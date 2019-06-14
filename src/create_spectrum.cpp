#include <regex>
#include <fstream>

#include "create_spectrum.h"
#include "util.h"

Spectrum load_spectrum(std::istream & input)
{
    Spectrum spectrum;
    std::string line;
    double multiplier = 1.0;

    spectrum.type = Spectrum_Type::FILE;

    while(std::getline(input, line))
    {
        std::string line_lower = to_lower(line);
        if(line_lower.find("description") != std::string::npos)
        {
            std::string description = line.substr(line.find(":") + 2);
            spectrum.description = description;
            continue;
        }
        if(line_lower.find("type") != std::string::npos)
        {
            continue;
        }
        if(line_lower.find("wavelength units") != std::string::npos)
        {
            if((line_lower.find("nanometer") != std::string::npos)
               || (line_lower.find("nm") != std::string::npos))
            {
                multiplier *= .001;
            }
            continue;
        }

        std::regex pattern("\\s*(\\S+)\\s+(\\S+)\\s*");
        std::smatch matches;

        if(std::regex_search(line, matches, pattern))
        {
            std::string wl = matches[1].str();
            std::string val = matches[2].str();
            spectrum.values.push_back(
              std::make_pair<double, double>(std::stod(wl) * multiplier, std::stod(val)));
        }
    }

    return spectrum;
}

Spectrum load_spectrum(std::string const & path)
{
    std::ifstream fin(path);
    return load_spectrum(fin);
}

Spectrum create_spectrum(std::string const & line, std::string const & standard_directory)
{
    Spectrum spectrum;

    if(line.find("None") != std::string::npos)
    {
        spectrum.type = Spectrum_Type::NONE;
        spectrum.description = "None";
    }
    else if(line.find("Blackbody") != std::string::npos && line.find(".SSP") == std::string::npos)
    {
        spectrum.type = Spectrum_Type::BLACKBODY;
        spectrum.description = "Blackbody";

        std::regex pattern(".*T=(.*)K\\)");
        // auto itr = std::sregex_iterator(line.begin(), line.end(), pattern);
        // std::string val = itr->str();
        std::smatch matches;
        if(std::regex_search(line, matches, pattern))
        {
            std::string val = matches[1].str();
            spectrum.t = std::stod(val);
        }
    }
    else if(line.find("UV Action") != std::string::npos && line.find(".SSP") == std::string::npos)
    {
        spectrum.type = Spectrum_Type::UV_ACTION;
        spectrum.description = "UV Action";
        std::regex pattern(".*a=(.*), b=(.*)\\)");
        // auto itr = std::sregex_iterator(line.begin(), line.end(), pattern);
        // std::string a = itr->str(1);
        // std::string a = itr->str(2);
        std::smatch matches;
        if(std::regex_search(line, matches, pattern))
        {
            std::string a = matches[1].str();
            std::string b = matches[2].str();
            spectrum.a = std::stod(a);
            spectrum.b = std::stod(b);
        }
    }
    else if((line.find("Krochmann") != std::string::npos)
            && (line.find(".SSP") == std::string::npos))
    {
        spectrum.type = Spectrum_Type::KROCHMANN;
        spectrum.description = "Krochmann";
    }
    else
    {
        std::string spectum_path = standard_directory;
        spectum_path += line;
        spectrum = load_spectrum(spectum_path);
    }

    return spectrum;
}
