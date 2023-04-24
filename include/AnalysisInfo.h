// Copyright 2023 Nicolò Salimbeni
#ifndef AnalysisInfo_h
#define AnalysisInfo_h

#include <string>
#include <vector>

class AnalysisInfo {
 public:
  AnalysisInfo(std::string &);
  ~AnalysisInfo();

  void TakeArgoments(std::string &);
  bool Contains(std::string);
  int  Value(std::string);

 private:
  std::vector<std::string> argoments;
};
#endif
