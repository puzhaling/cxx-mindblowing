#include <iostream> 
#include <cstring> // for std::strlen
#include <sstream> // for std::ostringstream
#include <fstream> // for std::ofstream

#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

#include "main_window.h"
#include "search_window.h"
#include "utils.h"

MainWindow::MainWindow(int w, int h, const char* title,
                       const char* read_path, const char* write_path) 
    : Fl_Window(w, h, title),
      write_path_(write_path) {
  begin();
    scroll_ = new Fl_Scroll(10, 10, w, h - 20);
    scroll_->begin();
      table_ = new MainTable(10, 10, scroll_->w() - 166, scroll_->h(), title, 
                             read_path, write_path);
    scroll_->end();

    close_and_save_ = new Fl_Button(980, 10, 90, 50, "Выйти и\nсохранить");
    add_ = new Fl_Button(980, 70, 90, 50, "Добавить");
    remove_ = new Fl_Button(980, 120, 90, 50, "Удалить");
    search_ = new Fl_Button(980, 170, 90, 50, "Поиск");
    debug_ = new Fl_Button(980, 230, 90, 50, "Печать\nСД");

    close_and_save_->callback(CloseWindowCb, this);
    add_->callback(AddUserInputCb, this);
    remove_->callback(RemoveUserInputCb, this);
    search_->callback(SearchUserInputCb, this);
    debug_->callback(DebugWindowCb, this);
  end();
}

void MainWindow::DropData() const {
  std::cout << "DropData: start dropping" << std::endl;
  std::ofstream out(write_path_, std::ios::trunc);
  // "formatting error!"!!!
  const auto* hashtable_data = table_->hashtable_.Data();
  for (int i = 0; i < HashTable::Size(); ++i) {
    auto nodes = hashtable_data[i].second.GetAllRBTreeNodes();
    for (int j = 0; j < nodes.size(); ++j) {
      if (i + 1 == HashTable::Size() && j + 1 == nodes.size())
       out << nodes[j];
      else
       out << nodes[j] << std::endl; 
    }
  }  
  out.close();
  std::cout << "DropData: dropping ends" << std::endl;
}

void MainWindow::CloseWindowCb(Fl_Widget* w, void* data) {
  MainWindow* win = static_cast<MainWindow*>(data);
  win->hide();
  win->DropData();
  Fl::delete_widget(w);
  exit(0);
}

void MainWindow::AddUserInputCb(Fl_Widget* w, void* data) {
  std::cerr << "AddUserInputCb: Creating input window" << std::endl;
  Fl_Window* input_window = new Fl_Window(400, 350, "Добавление записи");

  Fl_Input* passport_series = new Fl_Input(120, 10, 250, 25, "Паспорт серия:");
  Fl_Input* passport_number = new Fl_Input(120, 40, 250, 25, "Паспорт номер:");
  Fl_Input* car_make = new Fl_Input(120, 70, 250, 25, "Марка авто:");
  Fl_Input* car_model = new Fl_Input(120, 100, 250, 25, "Модель авто:");
  Fl_Input* name = new Fl_Input(120, 130, 250, 25, "Имя:");
  Fl_Input* surname = new Fl_Input(120, 160, 250, 25, "Фамилия:");
  Fl_Input* patronymic = new Fl_Input(120, 190, 250, 25, "Отчество:");
  Fl_Input* day = new Fl_Input(120, 220, 250, 25, "День:");
  Fl_Input* month = new Fl_Input(120, 250, 250, 25, "Месяц:");
  Fl_Input* year = new Fl_Input(120, 280, 250, 25, "Год:");

  Fl_Button* ok_button = new Fl_Button(120, 310, 100, 30, "OK");
  Fl_Button* cancel_button = new Fl_Button(230, 310, 100, 30, "Отмена");

  // Pass the main window and input window as user data
  ok_button->callback(AddUserInputOkButtonCb, new std::pair<MainWindow*, Fl_Window*>(reinterpret_cast<MainWindow*>(data), input_window));
  cancel_button->callback([](Fl_Widget*, void* v) {
    Fl_Window* win = (Fl_Window*)v;
    win->hide();
    delete win;
  }, input_window);

  input_window->end();
  input_window->set_modal();
  input_window->show();
}

void MainWindow::AddUserInputOkButtonCb(Fl_Widget* w, void* data) {
  auto* pair = static_cast<std::pair<MainWindow*, Fl_Window*>*>(data);
  MainWindow* main_window = pair->first;
  Fl_Window* input_window = pair->second;

  std::cerr << "AddUserInputOkButtonCb: Collecting data from inputs" << std::endl;

  // Collect data from inputs
  Fl_Input* passport_series = static_cast<Fl_Input*>(input_window->child(0));
  Fl_Input* passport_number = static_cast<Fl_Input*>(input_window->child(1));
  Fl_Input* car_make = static_cast<Fl_Input*>(input_window->child(2));
  Fl_Input* car_model = static_cast<Fl_Input*>(input_window->child(3));
  Fl_Input* name = static_cast<Fl_Input*>(input_window->child(4));
  Fl_Input* surname = static_cast<Fl_Input*>(input_window->child(5));
  Fl_Input* patronymic = static_cast<Fl_Input*>(input_window->child(6));
  Fl_Input* day = static_cast<Fl_Input*>(input_window->child(7));
  Fl_Input* month = static_cast<Fl_Input*>(input_window->child(8));
  Fl_Input* year = static_cast<Fl_Input*>(input_window->child(9));

  using std::strlen;
  if (!strlen(passport_series->value()) || !strlen(passport_number->value()) ||
      !strlen(car_make->value()) || !strlen(car_model->value()) || !strlen(patronymic->value()) ||
      !strlen(name->value()) || !strlen(surname->value()) || !strlen(day->value()) ||
      !strlen(month->value()) || !strlen(year->value())) {
    std::cerr << "Error: One or more input fields are missing." << std::endl;
    input_window->hide();
    delete input_window;
    delete pair;
    return;
  }

  Passport passport = {passport_series->value(), passport_number->value()};
  CarSpec car_spec = {car_make->value(), car_model->value()};
  FullName full_name = {surname->value(), name->value(), patronymic->value()};
  Date date = {day->value(), month->value(), year->value()};

  if (!IsValid(passport) || !IsValid(car_spec) || !IsValid(full_name) ||
      !IsValid(date)) {
    std::cerr << "Error: invalid formating." << std::endl;
    input_window->hide();
    delete input_window;
    delete pair;
    return;
  }

  // Insert data into the table
  main_window->table_->InsertRow(passport, car_spec, full_name, date);

  std::cerr << "AddUserInputOkButtonCb: Row inserted successfully" << std::endl;

  input_window->hide();
  delete input_window;
  delete pair;
}

void MainWindow::RemoveUserInputCb(Fl_Widget*, void* data) {
  std::cerr << "RemoveUserInput: Creating input window" << std::endl;
  Fl_Window* input_window = new Fl_Window(400, 350, "Удаление записи");

  Fl_Input* passport_series = new Fl_Input(120, 10, 250, 25, "Паспорт серия:");
  Fl_Input* passport_number = new Fl_Input(120, 40, 250, 25, "Паспорт номер:");
  Fl_Input* car_make = new Fl_Input(120, 70, 250, 25, "Марка авто:");
  Fl_Input* car_model = new Fl_Input(120, 100, 250, 25, "Модель авто:");
  Fl_Input* name = new Fl_Input(120, 130, 250, 25, "Имя:");
  Fl_Input* surname = new Fl_Input(120, 160, 250, 25, "Фамилия:");
  Fl_Input* patronymic = new Fl_Input(120, 190, 250, 25, "Отчество:");
  Fl_Input* day = new Fl_Input(120, 220, 250, 25, "День:");
  Fl_Input* month = new Fl_Input(120, 250, 250, 25, "Месяц:");
  Fl_Input* year = new Fl_Input(120, 280, 250, 25, "Год:");

  Fl_Button* ok_button = new Fl_Button(120, 310, 100, 30, "OK");
  Fl_Button* cancel_button = new Fl_Button(230, 310, 100, 30, "Отмена");

  // Pass the main window and input window as user data
  ok_button->callback(RemoveUserInputOkButtonCb, new std::pair<MainWindow*, Fl_Window*>(reinterpret_cast<MainWindow*>(data), input_window));
  cancel_button->callback([](Fl_Widget*, void* v) {
    Fl_Window* win = (Fl_Window*)v;
    win->hide();
    delete win;
  }, input_window);

  input_window->end();
  input_window->set_modal();
  input_window->show();
}

void MainWindow::RemoveUserInputOkButtonCb(Fl_Widget* w, void* data) {
  auto* pair = static_cast<std::pair<MainWindow*, Fl_Window*>*>(data);
  MainWindow* main_window = pair->first;
  Fl_Window* input_window = pair->second;

  std::cerr << "RemoveUserInputOkButtonCb: Collecting data from inputs" << std::endl;

  // Collect data from inputs
  Fl_Input* passport_series = static_cast<Fl_Input*>(input_window->child(0));
  Fl_Input* passport_number = static_cast<Fl_Input*>(input_window->child(1));
  Fl_Input* car_make = static_cast<Fl_Input*>(input_window->child(2));
  Fl_Input* car_model = static_cast<Fl_Input*>(input_window->child(3));
  Fl_Input* name = static_cast<Fl_Input*>(input_window->child(4));
  Fl_Input* surname = static_cast<Fl_Input*>(input_window->child(5));
  Fl_Input* patronymic = static_cast<Fl_Input*>(input_window->child(6));
  Fl_Input* day = static_cast<Fl_Input*>(input_window->child(7));
  Fl_Input* month = static_cast<Fl_Input*>(input_window->child(8));
  Fl_Input* year = static_cast<Fl_Input*>(input_window->child(9));

  using std::strlen;
  if (!strlen(passport_series->value()) || !strlen(passport_number->value()) ||
      !strlen(car_make->value()) || !strlen(car_model->value()) || !strlen(patronymic->value()) ||
      !strlen(name->value()) || !strlen(surname->value()) || !strlen(day->value()) ||
      !strlen(month->value()) || !strlen(year->value())) {
    std::cerr << "Error: One or more input fields are missing." << std::endl;
    input_window->hide();
    delete input_window;
    delete pair;
    return;
  }

  Passport passport = {passport_series->value(), passport_number->value()};
  CarSpec car_spec = {car_make->value(), car_model->value()};
  FullName full_name = {surname->value(), name->value(), patronymic->value()};
  Date date = {day->value(), month->value(), year->value()};

  if (!IsValid(passport) || !IsValid(car_spec) || !IsValid(full_name) ||
      !IsValid(date)) {
    std::cerr << "Error: invalid formating." << std::endl;
    input_window->hide();
    delete input_window;
    delete pair;
    return;
  }
 
  // remove data from the table
  main_window->table_->RemoveRow(passport, car_spec, full_name, date);

  std::cerr << "RemoveUserInputOkButtonCb: Row removed successfully" << std::endl;

  input_window->hide();
  delete input_window;
  delete pair;
}

void MainWindow::SearchUserInputCb(Fl_Widget* w, void* data) {
  std::cerr << "SearchUserInput: Creating input window" << std::endl;
  Fl_Window* input_window = new Fl_Window(400, 260, "Поиск записей"); 

  Fl_Input* passport_series = new Fl_Input(120, 10, 250, 25, "Паспорт серия:");
  Fl_Input* passport_number = new Fl_Input(120, 40, 250, 25, "Паспорт номер:");
  Fl_Input* car_make = new Fl_Input(120, 70, 250, 25, "Марка авто:");
  Fl_Input* car_model = new Fl_Input(120, 100, 250, 25, "Модель авто:");
  Fl_Input* day = new Fl_Input(120, 130, 250, 25, "День:");
  Fl_Input* month = new Fl_Input(120, 160, 250, 25, "Месяц:");
  Fl_Input* year = new Fl_Input(120, 190, 250, 25, "Год:");

  Fl_Button* ok_button = new Fl_Button(120, 220, 100, 30, "OK");
  Fl_Button* cancel_button = new Fl_Button(230, 220, 100, 30, "Отмена");

  // pass the main window and input window as user data
  ok_button->callback(SearchUserInputOkButtonCb, new std::pair<MainWindow*, Fl_Window*>(reinterpret_cast<MainWindow*>(data), input_window));
  cancel_button->callback([](Fl_Widget*, void* v) {
    Fl_Window* win = (Fl_Window*)v;
    win->hide();
    delete win;
  }, input_window);

  input_window->end();
  input_window->set_modal();
  input_window->show();
}

void MainWindow::SearchUserInputOkButtonCb(Fl_Widget* w, void* data) {
    auto* pair = static_cast<std::pair<MainWindow*, Fl_Window*>*>(data);
    MainWindow* main_window = pair->first;
    Fl_Window* input_window = pair->second;

    std::cerr << "SearchUserInputOkButtonCb: Collecting data from inputs" << std::endl;

    Fl_Input* passport_series = static_cast<Fl_Input*>(input_window->child(0));
    Fl_Input* passport_number = static_cast<Fl_Input*>(input_window->child(1));
    Fl_Input* car_make = static_cast<Fl_Input*>(input_window->child(2));
    Fl_Input* car_model = static_cast<Fl_Input*>(input_window->child(3));
    Fl_Input* day = static_cast<Fl_Input*>(input_window->child(4));
    Fl_Input* month = static_cast<Fl_Input*>(input_window->child(5));
    Fl_Input* year = static_cast<Fl_Input*>(input_window->child(6));

    using std::strlen;
    if (!strlen(passport_series->value()) || !strlen(passport_number->value()) ||
        !strlen(car_make->value()) || !strlen(car_model->value()) ||
        !strlen(day->value()) || !strlen(month->value()) || !strlen(year->value())) {
        std::cerr << "Error: One or more input fields are missing." << std::endl;
        input_window->hide();
        delete input_window;
        delete pair;
        return;
    }
    
    Passport passport = {passport_series->value(), passport_number->value()};
    CarSpec carspec = {car_make->value(), car_model->value()};
    Date date = {day->value(), month->value(), year->value()};

    if (!IsValid(passport) || !IsValid(carspec) || !IsValid(date)) {
      std::cerr << "Error: invalid formating." << std::endl;
      input_window->hide();
      delete input_window;
      delete pair;
      return;
    }

    std::vector<std::pair<RBTreeNode, int>> collection;
    const auto& hashtable = main_window->table_->hashtable_;
    hashtable.FindAll(passport, carspec, date, collection); 
    std::cout << "SearchUserInputOkButtonCb: " << collection.size() << " rows is found" << std::endl;

    SearchWindow* search_window = new SearchWindow(main_window->w(), main_window->h(), 
                                                   "Результаты поиска", main_window);
    search_window->table_->PopulateWith(collection);
    search_window->table_->rows(collection.size());
    main_window->hide();
    search_window->show();
    search_window->set_modal();

    input_window->hide();
    delete input_window;
    delete pair;
}

void MainWindow::DebugWindowCb(Fl_Widget* w, void* data) {
    MainWindow* main_window = static_cast<MainWindow*>(data);

    Fl_Window* debug_window = new Fl_Window(800, 600, "Печать СД");

    Fl_Text_Display* text_display = new Fl_Text_Display(10, 10, 780, 580);
    Fl_Text_Buffer* text_buffer = new Fl_Text_Buffer();

    std::ostringstream oss;
    const auto* hashtable_data = main_window->table_->hashtable_.Data();
    for (int i = 0; i < HashTable::Size(); ++i) {
      oss << "BUCKET POSITION: " << i << std::endl;
      const RBTree& tree = hashtable_data[i].second;
      tree.InorderTraversal(oss);
      oss << std::endl;
    }

    text_buffer->text(oss.str().c_str());
    text_display->buffer(text_buffer);

    debug_window->end();
    debug_window->show();    
}
