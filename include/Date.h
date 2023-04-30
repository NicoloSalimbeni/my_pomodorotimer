#ifndef Date_h
#define Date_h

#include <string>

#include "StateFile.h"

class Date {
 public:
  explicit Date(StateFile* file);
  ~Date();
  void        UpdateFileDate(std::string) const;  // update date inside the file
  void        UpdateTodayDate();     // update private member date_today
  std::string GetTodayDate() const;  // return date_today
  bool        IsToday() const;       // check if date_today == file_date

 private:
  StateFile*  file;
  std::string date_today;
  std::string file_date;
};

#endif
