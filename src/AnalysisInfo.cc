// Copyright 2023 Nicolò Salimbeni
#include "./../include/AnalysisInfo.h"

#include <iostream>
#include <sstream>
#include <string>
AnalysisInfo::AnalysisInfo(std::string &s) { TakeArgoments(s); }

AnalysisInfo::~AnalysisInfo() {}

void AnalysisInfo::TakeArgoments(std::string &s) {
  std::stringstream argoments_input(s);
  std::string       temp;
  while (argoments_input >> temp) {
    argoments.push_back(temp);
  }
}

bool AnalysisInfo::Contains(std::string to_find) {
  for (auto arg_n : argoments) {
    if (arg_n == "-" + to_find) {
      return true;
    }
  }
  return false;
}

int AnalysisInfo::Value(std::string to_find) {
  if (!Contains(to_find)) {
    return -1;
  }

  // find the value
  int position = 0;
  for (unsigned long int i = 0; i < argoments.size(); i++) {
    if (argoments[i] == ("-" + to_find)) {
      position = i + 1;
    }
  }
  return std::stoi(argoments[position]);
}
