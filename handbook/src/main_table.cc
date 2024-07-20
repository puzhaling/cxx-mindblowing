#include "main_table.h"

MainTable::MainTable(int x, int y, int w, int h, const char* title, 
             const char* read_path, const char* write_path) 
    : Fl_Table_Row(x, y, w, h, title), 
      hashtable_() {
  begin();
    hashtable_.PopulateFrom(read_path);
    data_ = hashtable_.GetAllNodes();
    rows(data_.size());
    cols(9);
    col_header(1);
    col_resize(1);
    row_header(1);
    row_resize(1);
  end();

  col_width(0, kColumnWidth);  // passport series 
  col_width(1, kColumnWidth);  // passport number
  col_width(2, kColumnWidth);  // car make
  col_width(3, kColumnWidth);  // car model
  col_width(4, kColumnWidth);  // surname
  col_width(5, kColumnWidth);  // name
  col_width(6, kColumnWidth);  // patronymic
  col_width(7, kColumnWidth);  // date
  col_width(8, kColumnWidth);  // line_number
}

void MainTable::draw_cell(TableContext context, int r, int c, int x, int y, 
                         int w, int h) {
  static char s[40];
  switch (context) {
  case CONTEXT_STARTPAGE:
    fl_font(FL_HELVETICA, 14);
    return;
  case CONTEXT_ROW_HEADER:
    snprintf(s, sizeof(s), "%d", r + 1);
    fl_push_clip(x, y, w, h);
    fl_draw_box(FL_THIN_UP_BOX, x, y, w, h, color());
    fl_color(FL_BLACK);
    fl_draw(s, x, y, w, h, FL_ALIGN_CENTER);
    fl_pop_clip();
    return;
  case CONTEXT_COL_HEADER:
    switch (c) {
    case 0: 
      snprintf(s, sizeof(s), "Серия"); 
      break;
    case 1: 
      snprintf(s, sizeof(s), "Номер"); 
      break;
    case 2: 
      snprintf(s, sizeof(s), "Марка авто"); 
      break;
    case 3: 
      snprintf(s, sizeof(s), "Модель авто"); 
      break;
    case 4: 
      snprintf(s, sizeof(s), "Фамилия"); 
      break;
    case 5: 
      snprintf(s, sizeof(s), "Имя"); 
      break;
    case 6: 
      snprintf(s, sizeof(s), "Отчество"); 
      break;
    case 7: 
      snprintf(s, sizeof(s), "Дата"); 
      break;
    case 8: 
      snprintf(s, sizeof(s), "Номер строки"); 
      break;
    }
    fl_push_clip(x, y, w, h);
    fl_draw_box(FL_THIN_UP_BOX, x, y, w, h, color());
    fl_color(FL_BLACK);
    fl_draw(s, x, y, w, h, FL_ALIGN_CENTER);
    fl_pop_clip();
    return;
  case CONTEXT_CELL:
    fl_push_clip(x, y, w, h);
    {
      fl_color(row_selected(r) ? FL_SELECTION_COLOR : FL_WHITE);
      fl_draw_box(FL_FLAT_BOX, x, y, w, h, fl_color());
      fl_color(FL_BLACK);
      const auto& node = data_[r];
      switch (c) {
      case 0: 
        snprintf(s, sizeof(s), "%s", node.passport.series.c_str()); 
        break;
      case 1: 
        snprintf(s, sizeof(s), "%s", node.passport.number.c_str()); 
        break;
      case 2: 
        snprintf(s, sizeof(s), "%s", node.carspec.make.c_str()); 
        break;
      case 3: 
        snprintf(s, sizeof(s), "%s", node.carspec.model.c_str()); 
        break;
      case 4: 
        snprintf(s, sizeof(s), "%s", node.fullname.surname.c_str()); 
        break;
      case 5: 
        snprintf(s, sizeof(s), "%s", node.fullname.name.c_str()); 
        break;
      case 6:
        snprintf(s, sizeof(s), "%s", node.fullname.patronymic.c_str()); 
        break;
      case 7: 
        snprintf(s, sizeof(s), "%s-%s-%s", 
                 node.date.day.c_str(), node.date.month.c_str(), 
                 node.date.year.c_str()); 
        break;
      case 8: 
        snprintf(s, sizeof(s), "%d", node.line_number); 
        break;
      }
      fl_draw(s, x, y, w, h, FL_ALIGN_CENTER);
      fl_color(FL_GRAY);
      fl_rect(x, y, w, h);
    }
    fl_pop_clip();
    return;
  default:
    return;
  }
}
