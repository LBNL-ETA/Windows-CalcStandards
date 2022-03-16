#include <algorithm>

#include "util.h"
namespace window_standards
{
    std::string to_lower(std::string s)
    {
        /*
                This has issues with unicode but there will be many of those to deal
                with if this ever needs to really be internationalized.
                Until then this should be good enough
        */
#ifdef _MSC_VER
#    pragma warning(push)
#    pragma warning(disable : 4244)
#endif
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
#ifdef _MSC_VER
#    pragma warning(pop)
#endif
        return s;
    }
}   // namespace window_standards
