#ifndef HANDBOOK_START_WINDOW_H_
#define HANDBOOK_START_WINDOW_H_

#include <string> 

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>

struct UserInputs {
  Fl_Input* read_from;
  Fl_Input* write_to;
  Fl_Input* ht_size;
};

class StartWindow {
 public:
  StartWindow();

  void Show() { win_.show(); }
  int htable_size() const;

 private:
  Fl_Window win_;
  Fl_Input* read_;
  Fl_Input* write_;
  Fl_Input* htable_size_;
  Fl_Button* save_;
  UserInputs inputs_;
};

void SaveUserInputs(Fl_Widget*, void*);

#endif // HANDBOOK_START_WINDOW_H_
