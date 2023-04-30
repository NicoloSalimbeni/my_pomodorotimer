// Copyright 2023 Nicolò Salimbeni
#include "./../include/Timer.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>

#include "./../include/Date.h"
#include "./../include/StateFile.h"

Timer::Timer(int b, int B, int f, int n, StateFile *state,
             std::string notify_path, std::string audio_path) {
  break_length      = b;
  long_break_length = B;
  focus_lenght      = f;
  n_short_breaks    = n;
  file              = state;
  audio_file        = audio_path;
  notify_file       = notify_path;
  date              = new Date(file);
  return;
}

void Timer::LoadCounts() {
  // this function decide the value of counts member. If the date of the state
  // file is different from today date the counter is set to zero and the date
  // of the file is updated. If the date of the file is the same of today the
  // counter is resumed with the number saved inside the file
  std::string today_date = date->GetTodayDate();
  std::string file_date  = file->ValueOf("date");
  if (file_date == today_date) {
    // if the date is the date of today load the counts from the file
    counts = std::stoi(file->ValueOf("counts"));
    return;
  } else if (file_date != today_date) {
    // check the date of the file, if it's not the same of today counts=0
    counts = 0;
    file->UpdateValueOf("counts", std::to_string(counts));
    file->UpdateValueOf("date", today_date);
    return;
  }

  std::cout << "error in loading the conts, counter set to 0" << std::endl;
  counts = 0;
  file->UpdateValueOf("counts", std::to_string(counts));
  return;
}

void Timer::PrintTimer(std::string type) {
  // print the value of the timer inside notify.txt and on screen
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
  // script from chatGPT
  //  Convert the duration from minutes to seconds
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

void Timer::LoadTimer() {
  // reeds when the last timer stopped, if it was stopped during a break nothing
  // happens, if it was stopped during a focus it resumes the timer
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
  int         string_size = time.size();
  for (auto j = 0; j < string_size; j++) {
    if (j < i) {
      minutes_s += time[j];
    } else if (j > i) {
      seconds_s += time[j];
    }
  }
  minutes = std::stoi(minutes_s);
  seconds = std::stoi(seconds_s);
  CountDown(minutes, seconds, "Focus");
  AddCount();
  return;
}

void Timer::RingBell() const {
  // play the bell using PulseAudio
  std::system(("paplay " + audio_file).c_str());
  return;
}

void Timer::Focus() {
  // start a Focus timer and the update the counter of completed timers
  CountDown(focus_lenght, 0, "Focus");
  AddCount();
  RingBell();
  return;
}

void Timer::ShortBreak() {
  // start a short break
  CountDown(break_length, 0, "Break");
  RingBell();
  return;
}

void Timer::LongBreak() {
  // start a long break
  CountDown(long_break_length, 0, "Long Break");
  RingBell();
  return;
}

void Timer::Break() {
  // decide if a short break or a long break is required based on if the decided
  // number of short breaks in a row was already done. In that case starts a
  // long break, otherwise a short one.
  if (counts % n_short_breaks == 0) {
    LongBreak();
  } else {
    Break();
  }
  return;
}

int Timer::GetCounts() const {
  // return the number of completed focus timers
  return counts;
}

void Timer::AddCount() {
  // add a count to the focus timer counter and update the value inside the
  // state file
  counts++;
  file->UpdateValueOf("counts", std::to_string(counts));
  return;
}
