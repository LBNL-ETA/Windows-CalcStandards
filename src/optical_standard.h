#ifndef WINDOW_STANDARDS_STANDARD_H_
#define WINDOW_STANDARDS_STANDARD_H_

#include <map>

#include "optical_standard_method.h"
namespace window_standards
{
    struct Optical_Standard
    {
        std::string name;
        std::string description;
        std::string file;
        std::map<Optical_Standard_Method_Type, Optical_Standard_Method> methods;
    };
}   // namespace window_standards
#endif
