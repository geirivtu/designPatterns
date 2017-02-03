#include <iostream>
#include <fstream>
#include <string>

#include "touppercase.h"
#include "addlinenumber.h"
#include "contains.h"
#include "filetansformer.h"
#include "prettyfier.h"

int main () {

  std::ifstream ifs ("test2.txt");

  ToUpperCase toUpper;
  AddLineNumber addLineNum;
  Contains contains_hei("hei");
  Prettyfier prettyFier;
  std::vector<Filter*> filters = {&contains_hei, &prettyFier, &addLineNum};

  std::stringstream stream;
  FileTansformer::applyFilters(ifs, stream, filters);

  std::string line;
  while (getline(stream, line)) {
    std::cout << line << std::endl;
  }

  return 0;
}
