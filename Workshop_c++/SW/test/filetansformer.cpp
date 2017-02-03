#include "filetansformer.h"

#include <iostream>
#include <experimental/optional>

void FileTansformer::applyFilters(std::istream &ifs, std::ostream &out, const std::vector<Filter *> &filters)
{
    std::string line;
    while (getline(ifs, line))
    {
        optstring string(line);
        for(Filter *filter : filters)
        {
            if(!string)
                break;

            string = filter->transform(string.value());
        }

        if(string)
            out << string.value() << "\n";
    }
}
