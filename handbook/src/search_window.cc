#include "search_window.h"

SearchWindow::SearchWindow(int w, int h, const char* title, 
                           MainWindow* window) 
    : Fl_Window(w, h, title),
      main_window_(window) {
  begin();
    Fl_Scroll* scroll = new Fl_Scroll(10, 10, w, h);
    scroll->begin();
      table_ = new SearchTable(10, 10, scroll->w() - 166, scroll->h(), title);
    scroll->end();
    return_ = new Fl_Button(980, 70, 80, 50, "Возврат");
    return_->callback(ReturnButtonCb, this);
  end();
}

void SearchWindow::ReturnButtonCb(Fl_Widget* w, void* data) {
  SearchWindow* search_window = static_cast<SearchWindow*>(data);
  search_window->hide();
  search_window->main_window_->show();
  delete search_window;
}
