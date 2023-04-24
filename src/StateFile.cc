// Copyright 2023 nicolò salimbeni
#include "./../include/StateFile.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

StateFile::StateFile(std::string path) {
  std::ifstream            file_in(path);
  std::vector<std::string> v_lines;
  std::string              line_tmp;
  while (std::getline(file_in, line_tmp)) {
    // ignore comments
    if (line_tmp[0] != '#') v_lines.push_back(line_tmp);
  }

  // fill file_info
  for (auto l : v_lines) {
    // TODO
  }
}
