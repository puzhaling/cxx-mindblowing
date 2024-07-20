#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>

#include "start_window.h"
#include "main_window.h"
#include "utils.h"

StartWindow::StartWindow(int w, int h, const char* title)
    : Fl_Window(w, h, title),
      read_(new Fl_Input(w/2, h/2, 150, 40, "Считать из файла:")),
      write_(new Fl_Input(w/2, h/2 + 60, 150, 40, "Записать в файл:")),
      save_(new Fl_Button(w/2, h/2 + 115, 90, 40, "Сохранить")) {
  begin();
    read_->labelsize(15);
    read_->textsize(15);
    write_->labelsize(15);
    write_->textsize(15);

    save_->callback(SaveUserInputCb, this);
  end();
}

void StartWindow::HandleSave() {
  if (!InputIsValid() || !PathIsValid(read_->value()) || 
      !PathIsValid(write_->value())) {
    std::cerr << "Error: invalid path" << std::endl;
    read_->value("");
    write_->value("");
    return;
  }
  std::cout << "HandleSave: success" << std::endl;

  const char* read_path = read_->value();
  const char* write_path  = write_->value();
  std::cout << "filepath to read from: " << read_path << '\n';
  std::cout << "filepath to write to: " << write_path << '\n';

  MainWindow* main_window = new MainWindow(w(), h(), label(), read_path, write_path); 
  main_window->show();
  hide();
  Fl::delete_widget(this);
}

void StartWindow::SaveUserInputCb(Fl_Widget* w, void* data) {
  StartWindow* start_window = static_cast<StartWindow*>(data);
  start_window->HandleSave();
} 
