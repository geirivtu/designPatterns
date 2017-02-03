#pragma once

#include "filter.h"

#include <fstream>
#include <vector>
#include <sstream>

class FileTansformer
{
public:

    static void applyFilters(std::istream &ifs, std::ostream &out, const std::vector<Filter *> &filters);
};

