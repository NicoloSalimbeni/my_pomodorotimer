// Copyright 2023 Nicolò Salimbeni
#include "./../include/Timer.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>

#include "./../include/StateFile.h"

Timer::Timer(int b, int B, int f, int c, StateFile *state,
             std::string notify_path, std::string audio_path) {
  break_length      = b;
  long_break_length = B;
  focus_lenght      = f;
  counts            = c;
  file              = state;
  audio_file        = audio_path;
  notify_file       = notify_path;

  return;
}

void Timer::PrintTimer(std::string type) {
  std::cout << "\r"
            << "(" << counts << ") " << type + ": " << timer_min << ":"
            << timer_sec << std::flush;
  std::ofstream out(notify_file.c_str());
  out << "(" << counts << ") " << type + ": " << timer_min << ":" << timer_sec
      << std::endl;

  // if Focus update also the state file
  if (type == "Focus") {
    std::string time =
        std::to_string(timer_min) + ":" + std::to_string(timer_sec);
    file->UpdateValueOf("last_timer", time);
  }

  // if Break or Long Break just write break
  if (type == "Break" || type == "Long Break") {
    file->UpdateValueOf("last_timer", "break");
  }

  return;
}

void Timer::CountDown(int minutes_in, int seconds_in, std::string type) {
  // Convert the duration from minutes to seconds
  int duration_seconds = minutes_in * 60 + seconds_in;

  // Countdown loop
  timer_min = duration_seconds / 60;
  timer_sec = duration_seconds % 60;
  for (; timer_min >= 0; --timer_min) {
    for (; timer_sec >= 0; --timer_sec) {
      PrintTimer(type);
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    timer_sec = 59;
  }

  return;
}

void Timer::LoadTime() {
  if (file == nullptr) {
    std::cout << "can't resume timer, state file not found" << std::endl;
    return;
  } else if (file->ValueOf("last_timer") == "break") {
    std::cout << "Timer stopped during a break, it's time to focus!"
              << std::endl;
    Focus();
    return;
  }
  std::string time = file->ValueOf("last_timer");

  int         minutes;
  int         seconds;
  int         i = time.find(':');
  std::string minutes_s;
  std::string seconds_s;
  for (int j = 0; j < time.size(); j++) {
    if (j < i) {
      minutes_s += time[j];
    } else if (j > i) {
      seconds_s += time[j];
    }
  }
  minutes = std::stoi(minutes_s);
  seconds = std::stoi(seconds_s);
  CountDown(minutes, seconds, "Focus");
}

void Timer::RingBell() {
  std::system(("paplay " + audio_file).c_str());
  return;
}

void Timer::Focus() {
  CountDown(focus_lenght, 0, "Focus");
  counts++;
  RingBell();
  return;
}

void Timer::Break() {
  CountDown(break_length, 0, "Break");
  RingBell();
  return;
}

void Timer::LongBreak() {
  CountDown(long_break_length, 0, "Long Break");
  RingBell();
  return;
}
