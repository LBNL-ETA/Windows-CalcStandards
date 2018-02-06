#ifndef WINDOWS_STANDARDS_HPP
#define WINDOWS_STANDARDS_HPP

#include <string>
#include <fstream>
#include <tchar.h>
#include <vector>

struct Standard_Curve
{
  Standard_Curve(std::basic_string<TCHAR> const& curve_description, std::basic_string<TCHAR> const& curve_type, std::basic_string<TCHAR> const& curve_wavelength_unit, std::vector<std::pair<double, double> > const& curve_wavelength_data);

  std::basic_string<TCHAR> description;
  std::basic_string<TCHAR> type;
  std::basic_string<TCHAR> wavelength_unit;
  std::vector<std::pair<double, double> > wavelength_data;
};

Standard_Curve load_curve_from_file(std::basic_string<TCHAR> const& path);

#endif