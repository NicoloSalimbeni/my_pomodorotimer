// Copyright 2023 Nicolò Salimbeni
#ifndef Timer_h
#define Timer_h

#include <string>

#include "./StateFile.h"

class Timer {
 public:
  Timer(int b, int B, int f, int c, int s, StateFile *state,
        std::string notify_path, std::string audio_path);
  void Focus();
  void Break();
  void LoadTime();
  void CountDown(int minutes, int seconds,
                 std::string type);   // update private memebers
  void PrintTimer(std::string type);  // print on screen and notify

 private:
  // minutes and seconds
  int timer_min;
  int timer_sec;

  // usefull members
  StateFile  *file;
  std::string audio_file;
  int         break_length;
  int         long_break_length;
  int         focus_lenght;
  int         counts;
  int         n_short_breaks;
  std::string notify_file;
};

#endif
