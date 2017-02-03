#pragma once

#include "filter.h"

class Contains : public Filter
{
public:
    Contains(const std::string &subStr) : subStr(subStr) {}

    // Filter interface
public:
    optstring transform(const std::string &line) override;

private:
    const std::string subStr;
};

