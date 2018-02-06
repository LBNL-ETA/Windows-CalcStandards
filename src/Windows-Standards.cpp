// Windows-Standards.cpp : Defines the exported functions for the DLL application.
//

#include "Windows-Standards.hpp"
#include <sstream>
#include <Error.h>
#include <stdlib.h>


Standard_Curve::Standard_Curve(std::basic_string<TCHAR> const& curve_description, std::basic_string<TCHAR> const& curve_type, std::basic_string<TCHAR> const& curve_wavelength_unit, std::vector<std::pair<double, double> > const& curve_wavelength_data)
  : description(curve_description), type(curve_type), wavelength_unit(curve_wavelength_unit), wavelength_data(curve_wavelength_data)
{}

Standard_Curve load_curve_from_file(std::basic_string<TCHAR> const& path)
{
  std::basic_ifstream<TCHAR> fin(path);
  if(!fin.is_open())
  {
    std::stringstream msg;
    msg << "Error opening file " << path.c_str();
    throw std::runtime_error(msg.str());
  }

  std::basic_string<TCHAR> description_str = _T("Description: ");
  std::basic_string<TCHAR> type_str = _T("Type: ");
  std::basic_string<TCHAR> wavelength_unit_str = _T("Wavelength Units: ");
  std::basic_string<TCHAR> description;
  std::basic_string<TCHAR> type;
  std::basic_string<TCHAR> wavelength_unit;
  std::vector<std::pair<double, double> > wavelength_data;

  for(std::basic_string<TCHAR> line; std::getline(fin, line);)
  {
    std::size_t found_pos;
    found_pos = line.find(description_str);
    if(found_pos != std::basic_string<TCHAR>::npos)
    {
      description = line.substr(description_str.size());
      continue;
    }
    found_pos = line.find(type_str);
    if(found_pos != std::basic_string<TCHAR>::npos)
    {
      type = line.substr(type_str.size());
      continue;
    }
    found_pos = line.find(wavelength_unit_str);
    if(found_pos != std::basic_string<TCHAR>::npos)
    {
      wavelength_unit = line.substr(wavelength_unit_str.size());
      continue;
    }
    
    if(line.size() == 0)
    {
      continue;
    }

    double x = _tstof(line.substr(0, line.find(_T(" "))).c_str());
    double y = _tstof(line.substr(line.find(_T(" "))).c_str());
    wavelength_data.push_back(std::make_pair(x, y));
  }

  Standard_Curve curve(description, type, wavelength_unit, wavelength_data);
  return curve;
}


