#ifndef Date_h
#define Date_h

#include <string>

class Date {
 public:
  explicit Date(const std::string s);
  ~Date();
  void        LoadFromFile();
  void        UpdateFileDate(std::string);
  std::string TodayDate();
  bool        IsToday(std::string);
  void        UpdateFile();

 private:
  std::string path;
  std::string date_today;
};

#endif
