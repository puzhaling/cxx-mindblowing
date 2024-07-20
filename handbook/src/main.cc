#include <iostream>

#include <FL/Fl.H>

#include "start_window.h"
#include "hashtable.h"

int main() {
  constexpr int kWindowWidth = 1110;
  constexpr int kWindowHeight = 840;
  constexpr const char* kWindowName = "Справочник";

  StartWindow* start_window = new StartWindow(kWindowWidth, kWindowHeight, kWindowName); 
  start_window->show();

  return Fl::run();
}

