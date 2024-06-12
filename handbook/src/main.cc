#include <FL/Fl.H>

#include "start_window.h"

int main(int argc, char** argv) {
  StartWindow win1;
  win1.Show();

  return Fl::run();
}
