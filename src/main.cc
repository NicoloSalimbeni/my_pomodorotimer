// Copyright 2023 Nicolò Salimbeni
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "./../include/AnalysisInfo.h"
#include "./../include/Date.h"
#include "./../include/StateFile.h"
#include "./../include/Timer.h"

void print(std::string s) {
  /*
   print inside notify and on screen a string
   */
  std::cout << "\r" << s << std::flush;
  std::ofstream out("./files/notify.txt");
  out << s << std::endl;
  return;
}

int main(int argc, char* argv[]) {
  // ======= take initial parameters and build the AnalysisInfo =======
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

  // =========== built objects to manage date, state file and timer ===========

  StateFile* state_file = new StateFile("files/state_file.txt");
  Timer* timer = new Timer(break_duration, long_break_duration, timer_duration,
                           n_short_breaks, state_file, "files/notify.txt",
                           "files/bell_1.wav");
  Date*  date  = new Date(state_file);

  // =========== start the timer ===========

  // fist check if the the date in the state file is the date of today AND if
  // the timer wasn't stopped during a break, if the conditions are true ask if
  // the user want to resume the last timer
  if (date->IsToday() && state_file->ValueOf("last_timer") != "break") {
    timer->LoadCounts();  // FIXME: bad practice, this as a side effect update
                          // the date inside the state file
    std::string resume;
    std::string last_timer  = state_file->ValueOf("last_timer");
    std::string last_counts = state_file->ValueOf("counts");
    std::cout << "Last timer was: " + last_counts + " counts and " +
                     last_timer + " left"
              << std::endl;
    do {
      std::cout << "Do you want to resume it? y/n: " << std::flush;
      std::getline(std::cin, resume);
    } while (resume != "y" && resume != "n");

    if (resume == "y") {
      timer->LoadTimer();

      // ask: start or skip the break?
      std::string br;
      do {
        print("Break? start (Enter), jump (j) ");
        std::getline(std::cin, br);
      } while (br != "j" && br != "");
      if (br == "") {
        timer->Break();
      }
    }
  }

  // load counts, if it was done before to resume the timer nothing happens, but
  // if it wasn't done it resumes the last counter or start from zero if the
  // date is changed.
  timer->LoadCounts();
  do {
    timer->Focus();
    print("Break? start (Enter), jump (j) ");

    std::string choice;
    do {
      std::getline(std::cin, choice);
    } while (choice != "" && choice != "j");

    // ask: start or skip the break?
    if (choice == "j") {
      continue;
    } else {
      timer->Break();
    }

    print("Press enter to focus");
    std::string tmp;
    std::getline(std::cin, tmp);
  } while (true);

  return 0;
}
