#include "touppercase.h"

#include <algorithm>

optstring ToUpperCase::transform(const std::string &line)
{
    std::string out(line);
    std::transform(out.begin(), out.end(), out.begin(), ::toupper);
    return optstring(out);
}
