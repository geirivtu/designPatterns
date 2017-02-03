#include "prettyfier.h"

#include <algorithm>

optstring Prettyfier::transform(const std::string &line)
{
    int diff = std::count(line.begin(), line.end(), '{') -
            std::count(line.begin(), line.end(), '}');

    std::string tabstr;
    auto addTabs = [&](){
        for(int i=0; i<tabs; ++i)
            tabstr += "\t";
    };

    if(diff > 0)
    {
        addTabs();
        tabs += diff;
    }
    else
    {
        tabs += diff;
        addTabs();
    }

    return tabstr + std::string(line);
}

