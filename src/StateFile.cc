// Copyright 2023 nicolò salimbeni
#include "./../include/StateFile.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

StateFile::StateFile(std::string path) : file_path(path) {
  std::ifstream            file_in(file_path);
  std::vector<std::string> v_lines;
  std::string              line_tmp;
  while (std::getline(file_in, line_tmp)) {
    // fill the vector with file lines
    all_file.push_back(line_tmp);

    // fill the map with usefull information
    if (line_tmp[0] != '#') v_lines.push_back(line_tmp);
  }

  // fill file_info
  for (auto line : v_lines) {
    std::stringstream line_out(line);
    std::string       key;
    std::string       value;
    line_out >> key;
    line_out >> value;
    key.erase(key.size() - 1, 1);
    info.insert({key, value});
  }
  return;
}

bool StateFile::Contains(std::string key) {
  auto it = info.find(key);
  if (it != info.end())
    return true;
  else
    return false;
}

std::string StateFile::ValueOf(std::string key) {
  auto it = info.find(key);
  if (it != info.end())
    return it->second;
  else
    std::cout << "error, can't find the key: " + key << std::endl;
  return "";
}

void StateFile::UpdateValueOf(std::string key, std::string value) {
  // update map
  auto it = info.find(key);
  if (it == info.end()) {
    std::cout << key << " not found, can't update its value" << std::endl;
    return;
  }
  it->second = value;
  // update the vector which will be printed
  int n_lines = all_file.size();
  for (int i = 0; i < n_lines; i++) {
    if (all_file[i].find(key) != std::string::npos) {
      all_file[i] = key + ": " + value;
    }
  }
  return;
}

void StateFile::PrintAll() {
  for (auto line : all_file) {
    std::cout << line << std::endl;
  }
  return;
}

void StateFile::UpdateFile() {
  std::ofstream file_out(file_path);
  for (auto line : all_file) {
    file_out << line << std::endl;
  }
  return;
}
