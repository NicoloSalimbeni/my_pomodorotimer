#ifndef Date_h
#define Date_h

#include <string>

#include "StateFile.h"

class Date {
 public:
  explicit Date(StateFile* file);
  ~Date();
  void        UpdateFileDate(std::string);
  std::string UpdateTodayDate();
  std::string GetTodayDate();
  bool        IsToday(std::string);

 private:
  StateFile*  file;
  std::string date_today;
  std::string file_date;
};

#endif
