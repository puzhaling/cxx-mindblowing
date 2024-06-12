#include <filesystem>
#include <string>
#include <algorithm>
#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>

#include "start_window.h"

constexpr int kWindowWidth = 1024;
constexpr int kWindowHeight = 768;

StartWindow::StartWindow()
    : win_(kWindowWidth, kWindowHeight, "Handbook") { 
  win_.begin();
    read_ = new Fl_Input(kWindowWidth/2, kWindowHeight/2, 150, 20, "Read from file:");
    write_ = new Fl_Input(kWindowWidth/2, kWindowHeight/2 + 30, 150, 20, "Write to file:");
    htable_size_ = new Fl_Input(kWindowWidth/2, kWindowHeight/2 + 60, 150, 20, "HashTable init. size:");
    save_ = new Fl_Button(kWindowWidth/2, kWindowHeight/2 + 85, 70, 20, "Save");
  win_.end();

  inputs_ = {read_, write_, htable_size_};
  save_->callback(SaveUserInputs, &inputs_);
}

int StartWindow::htable_size() const {
  return std::stoi(htable_size_->value());
}

void SaveUserInputs(Fl_Widget* w, void* iw) {
  namespace fs = std::filesystem;

  UserInputs* inputs = static_cast<UserInputs*>(iw);
  fs::path read_path(inputs->read_from->value()); 
  fs::path write_path(inputs->write_to->value());

  inputs->read_from->value("");
  inputs->write_to->value("");
  inputs->ht_size->value(""); 
  
  if (read_path.empty() || write_path.empty())
    return;

  constexpr const char* kDefaultHashTableSize = "8";
  if (inputs->ht_size->value() == "")
    inputs->ht_size->value(kDefaultHashTableSize);
  
  Fl_Window* widget_owner_window = inputs->read_from->window();
  widget_owner_window->hide();
} 
