// Copyright 2023 Nicolò Salimbeni
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

#include "./Utilities/AnalysisInfo.h"

int main(int argc, char* argv[]) {
  // take initial parameters and build the AnalysisInfo
  std::string initial_paramters;
  for (int i = 0; i < argc; i++) {
    initial_paramters += argv[i];
    initial_paramters += " ";
    // std::cout << argv[i] << std::endl;
  }
  AnalysisInfo* info = new AnalysisInfo(initial_paramters);

  // show help page if requested
  if (info->Contains("h")) {
    std::system("cat docs/help.txt");
    return -1;
  }

  // import all usefull parameters in minutes
  int timer_duration      = info->Value("t");
  int break_duration      = info->Value("b");
  int long_break_duration = info->Value("B");
  int n_short_breaks      = info->Value("s");

  // set my defaul values
  if (timer_duration == -1) {
    timer_duration = 50;
  }
  if (break_duration == -1) {
    break_duration = 10;
  }
  if (n_short_breaks == -1) {
    n_short_breaks = 3;
  }
  if (long_break_duration == -1) {
    long_break_duration = 20;
  }

  std::cout << timer_duration << " " << break_duration << " " << n_short_breaks
            << std::endl;
  return 0;
}
