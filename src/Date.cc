#include "./../include/Date.h"

#include <ctime>
#include <string>

#include "./../include/StateFile.h"

Date::Date(StateFile* s) : file(s) {
  date_today = UpdateTodayDate();
  file_date  = file->ValueOf("date");
  return;
}

Date::~Date() {}

std::string Date::UpdateTodayDate() {
  // Get the current time
  // Get the current time as a time_t object
  time_t current_time = time(nullptr);

  // Convert the time_t object to a tm structure
  tm time_info;
  localtime_r(&current_time, &time_info);

  // Extract the day, month, and year from the tm structure
  int day   = time_info.tm_mday;
  int month = time_info.tm_mon + 1;
  int year  = time_info.tm_year + 1900;

  // Save the date string in the dd/mm/yyyy format to a variable
  std::string date_string = std::to_string(day) + "/" + std::to_string(month) +
                            "/" + std::to_string(year);
  return date_string;
}

void Date::UpdateFileDate(std::string new_date) {
  file->UpdateValueOf("date", new_date);
  file->UpdateFile();
  return;
}

std::string Date::GetTodayDate() { return date_today; }
