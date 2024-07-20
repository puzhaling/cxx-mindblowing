#ifndef HANDBOOK_MAIN_WINDOW_H_
#define HANDBOOK_MAIN_WINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Scroll.H>

#include "main_table.h"

class MainWindow : public Fl_Window {
 public:
  MainWindow(int w, int h, const char* title, 
             const char* read_path, const char* write_path);

  void DropData() const;

 private:
  Fl_Scroll* scroll_;
  MainTable* table_;

  std::string write_path_;

  Fl_Button* close_and_save_;
  Fl_Button* add_;
  Fl_Button* remove_;
  Fl_Button* search_;  
  Fl_Button* debug_;

  static void AddUserInputOkButtonCb(Fl_Widget*, void*);
  static void RemoveUserInputOkButtonCb(Fl_Widget*, void*);
  static void SearchUserInputOkButtonCb(Fl_Widget*, void*);

  static void CloseWindowCb(Fl_Widget*, void*);
  static void AddUserInputCb(Fl_Widget*, void*);
  static void RemoveUserInputCb(Fl_Widget*, void*);
  static void SearchUserInputCb(Fl_Widget*, void*);
  static void DebugWindowCb(Fl_Widget*, void*);
};

#endif // HANDBOOK_MAIN_WINDOW_H_
