// Copyright 2023 Nicolò Salimbeni
#ifndef Timer_h
#define Timer_h

#include <string>

#include "./Date.h"
#include "./StateFile.h"

class Timer {
 public:
  Timer(int b, int B, int f, int n, StateFile *state, std::string notify_path,
        std::string audio_path);
  void Focus();       // starts a focus timer
  void ShortBreak();  // starts a short break
  void LongBreak();   // starts a long break
  void Break();       // decide which break is needed and starts it
  void LoadTimer();   // load the timer from state file and starts it
  void CountDown(int minutes, int seconds,
                 std::string type);   // countdown
  void PrintTimer(std::string type);  // print on screen and inside notify file
  void RingBell() const;              // ring the bell audio
  int  GetCounts() const;             // return the number of complited timers
  void LoadCounts();                  // load the proper number of counts
  void AddCount();                    // add one count to the counter

 private:
  // minutes and seconds of the timer
  int timer_min;
  int timer_sec;

  // usefull members
  StateFile  *file;               // state file pointer
  std::string audio_file;         // audio file path
  int         break_length;       // in minutes
  int         long_break_length;  // in minutes
  int         focus_lenght;       // in minutes
  int         counts;             // number of completed focus timers
  int         n_short_breaks;     // number of short breaks ina row
  std::string notify_file;        // path to notify.txt file
  Date       *date;               // pointer to menage the date
};

#endif
