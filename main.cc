// Copyright 2023 Nicolò Salimbeni
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>

#include "./Utilities/AnalysisInfo.h"

void print(std::string s) {
  std::cout << "\r" << s << std::flush;
  std::ofstream out("notify.txt");
  out << s << std::endl;
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
        std::cout << "\rTimer finished!" << std::endl;
        std::system("paplay ./audio/bell_1.wav");
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

  do {
    countdown(timer_duration, "Focus", count);
    count++;
    print("Break? exit (e), jump (j), start (s) ");
    std::cin >> state;
    if (state == "e") {
      break;
    } else if (state == "s") {
      if (count % 3 == 0) {
        countdown(long_break_duration, "Long break", count);
      } else {
        countdown(break_duration, "Break", count);
      }
    } else if (state == "j") {
      continue;
    }
    if (keep_going) {
      print("Press any key to focus");
      std::string tmp;
      std::cin >> tmp;
      std::cout << "\r" << std::endl;
    }
  } while (keep_going);
  print("No timer running");

  return 0;
}
