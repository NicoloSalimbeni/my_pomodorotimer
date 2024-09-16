#include "./../include/Date.h"

#include <ctime>
#include <iostream>
#include <string>

#include "./../include/StateFile.h"

Date::Date(StateFile* s) : file(s) {
  UpdateTodayDate();                  // load today date
  file_date = file->ValueOf("date");  // load date from file
  return;
}

Date::~Date() {}

void Date::UpdateTodayDate() {
  // save today date inside the private member of the object date_today as a
  // string in the format DD/MM/YYYY

  // script from chatGPT
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
  date_today = date_string;
  return;
}

void Date::UpdateFileDate(std::string new_date) const {
  // write inside the state file the new date
  file->UpdateValueOf("date", new_date);
  return;
}

std::string Date::GetTodayDate() const {
  // return today date in a string in the format DD/MM/YYYY
  return date_today;
}

bool Date::IsToday() const {
  // return a bool that tells if the date_today is the same as the file_date
  // inside the state file
  if (date_today == file_date) {
    return true;
  }
  return false;
}
