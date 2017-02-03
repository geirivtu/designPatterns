#pragma once

#include "filter.h"


class AddLineNumber : public Filter
{
    // Filter interface
public:
    optstring transform(const std::string &line) override;

private:
    int lineNumber {0};
};

