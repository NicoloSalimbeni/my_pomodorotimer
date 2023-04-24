// Copyright 2023 Nicolò Salimbeni
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>
#include <strstream>
#include <thread>

#include "./../include/AnalysisInfo.h"

void print(std::string s) {
  std::cout << "\r" << s << std::flush;
  std::ofstream out("./files/notify.txt");
  out << s << std::endl;
  return;
}

std::string date() {
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

int load_counts_from_file() {
  // load values from file
  std::ifstream in("./files/date.txt");
  std::string   date_file;
  std::string   count_file_s;
  int           count_file;
  std::getline(in, date_file);  // useless
  std::getline(in, count_file_s);
  count_file = std::stoi(count_file_s);

  return count_file;
}

void update_count_file(int count) {
  // write current count value}
  std::ofstream out("./files/date.txt");
  out << date() << std::endl;
  out << count << std::endl;

  return;
}

void countdown(int duration_minutes, std::string type, int count) {
  // Convert the duration from minutes to seconds
  int duration_seconds = duration_minutes * 60;

  // Countdown loop
  int minutes = duration_seconds / 60;
  int seconds = duration_seconds % 60;
  for (; minutes >= 0; --minutes) {
    for (; seconds >= 0; --seconds) {
      if (minutes == 0 && seconds == 0) {
        std::system("paplay ./files/bell_1.wav");
      } else {
        print("(" + std::to_string(count) + ") " + type + ": " +
              std::to_string(minutes) + ":" + std::to_string(seconds));
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    seconds = 59;
  }
  return;
}

int main(int argc, char* argv[]) {
  // take initial parameters and build the AnalysisInfo
  std::string initial_paramters;
  for (int i = 0; i < argc; i++) {
    initial_paramters += argv[i];
    initial_paramters += " ";
    // std::cout << argv[i] << std::endl;
  }
  AnalysisInfo* info = new AnalysisInfo(initial_paramters);

  // show help page if requested
  if (info->Contains("h")) {
    std::system("cat docs/help.txt");
    return -1;
  }

  // import all usefull parameters in minutes
  int timer_duration      = info->Value("t");
  int break_duration      = info->Value("b");
  int long_break_duration = info->Value("B");
  int n_short_breaks      = info->Value("s");

  // set my defaul values
  if (timer_duration == -1) {
    timer_duration = 50;
  }
  if (break_duration == -1) {
    break_duration = 10;
  }
  if (n_short_breaks == -1) {
    n_short_breaks = 3;
  }
  if (long_break_duration == -1) {
    long_break_duration = 20;
  }

  bool        keep_going = true;
  std::string state;
  int         count = 0;

  // check if the day of today is the same of the file
  std::string today_date = date();
  std::string file_date;

  std::ifstream in_date("./files/date.txt");
  std::getline(in_date, file_date);

  if (file_date == today_date) {  // load the value of count
    count = load_counts_from_file();
  } else {
    update_count_file(0);
  }

  do {
    countdown(timer_duration, "Focus", count);
    count++;
    update_count_file(count);
    print("Break? start (Enter), jump (j) ");
    std::getline(std::cin, state);
    if (state == "j") {
      continue;
    } else {
      if (count % 3 == 0) {
        countdown(long_break_duration, "Long break", count);
      } else {
        countdown(break_duration, "Break", count);
      }
    }
    if (keep_going) {
      print("Press enter to focus");
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::string tmp;
      std::getline(std::cin, tmp);
    }
  } while (keep_going);

  return 0;
}
