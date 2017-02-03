#pragma once

#include <filter.h>

class Prettyfier : public Filter
{
    // Filter interface
public:
    optstring transform(const std::string &line) override;

private:
    int tabs {0};
};

