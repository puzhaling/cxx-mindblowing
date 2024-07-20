#ifndef HANDBOOK_START_WINDOW_H_
#define HANDBOOK_START_WINDOW_H_

#include <cstring> // for std::strlen

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>

class StartWindow : public Fl_Window {
 public:
  StartWindow(int w, int h, const char* title);
  
 private:
  Fl_Input* read_;
  Fl_Input* write_;
  Fl_Button* save_;

  void HandleSave();
  bool InputIsValid();

  static void SaveUserInputCb(Fl_Widget*, void*);
};

inline bool StartWindow::InputIsValid() {
  const char* read_value = read_->value();
  const char* write_value = write_->value();
  return read_value && std::strlen(read_->value()) 
    && write_value && std::strlen(write_->value());
}

#endif // HANDBOOK_START_WINDOW_H_
