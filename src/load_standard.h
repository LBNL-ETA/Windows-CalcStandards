#ifndef WINDOWS_STANDARDS_LOAD_STANDARD_H_
#define WINDOWS_STANDARDS_LOAD_STANDARD_H_

#include <string>
#include <filesystem>

#include "standard.h"

Standard load_standard(std::istream & in, std::filesystem::path const& standard_directory);
Standard load_standard(std::filesystem::path const& path);
Standard load_standard(std::string const& path);

#endif
