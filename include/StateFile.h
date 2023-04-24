// Copyright 2023 nicolò salimbeni
#ifndef StateFile_h
#define StateFile_h

#include <map>
#include <string>
#include <vector>

class StateFile {
 public:
  explicit StateFile(std::string path);
  std::string ValueOf(std::string key);
  void        UpdateValueOf(std::string key, std::string value);
  void        PrintAll();
  void        UpdateFile();
  bool        Contains(std::string key);

 private:
  // cointains all lines, also comments
  std::vector<std::string> all_file;
  // contains only usefull information for the program
  std::map<std::string, std::string> info;
  // path to the state file
  std::string file_path;
};

#endif
