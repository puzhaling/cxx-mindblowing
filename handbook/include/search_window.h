#ifndef HANDBOOK_SEARCH_WINDOW_H_
#define HANDBOOK_SEARCH_WINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Scroll.H>

#include "main_window.h"
#include "search_table.h"

class SearchWindow : public Fl_Window {
 public:
  SearchWindow(int w, int h, const char* title, 
               MainWindow* window);

  friend class MainWindow;

 private:
  Fl_Button* return_;
  Fl_Scroll* scroll_;
  SearchTable* table_;

  MainWindow* main_window_;

  static void ReturnButtonCb(Fl_Widget*, void*);
};

#endif // HANDBOOK_SEARCH_WINDOW_H_
