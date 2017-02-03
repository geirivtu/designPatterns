#include "contains.h"

#include <iostream>

optstring Contains::transform(const std::string &line)
{
    if (line.find(subStr) != std::string::npos)
    {
        std::cout << "found substr: " << subStr << " in " << line << std::endl;
        return optstring(line);
    }
    return optstring();
}
