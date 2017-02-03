#pragma once

#include "filter.h"

class ToUpperCase : public Filter
{
    // Filter interface
public:
    optstring transform(const std::string &line) override;
};
