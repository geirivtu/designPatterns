#include "addlinenumber.h"


optstring AddLineNumber::transform(const std::string &line)
{
    std::string out(line);

    out = std::to_string(lineNumber++) + std::string(" : ") + out;

    return optstring(out);
}
