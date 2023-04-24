// Copyright 2023 nicolò salimbeni
#ifndef StateFile_h
#define StateFile_h

#include <string>
#include <vector>

class StateFile {
 public:
  explicit StateFile(std::string path);
  std::string ValueOf(std::string tag);

 private:
  std::vector<std::string> file_info;
};

#endif
