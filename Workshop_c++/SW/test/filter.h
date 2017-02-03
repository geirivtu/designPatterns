#pragma once

#include <string>
#include <experimental/optional>

using optstring = std::experimental::optional<std::string>;

class Filter
{
public:
    Filter();

    virtual optstring transform(const std::string& line) = 0;
};

