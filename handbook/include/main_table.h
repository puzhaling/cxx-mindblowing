#ifndef HANDBOOK_MAIN_TABLE_H_
#define HANDBOOK_MAIN_TABLE_H_

#include <vector>
#include <unordered_map>

#include <FL/Fl.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Table_Row.H>
#include <FL/fl_draw.H>  

#include "hashtable.h"
#include "rbtree.h"

class MainTable : public Fl_Table_Row {
 public:
  MainTable(int x, int y, int w, int h, const char* title, 
            const char* read_path, const char* write_path);

  void InsertRow(const Passport&, const CarSpec&, const FullName&,
                 const Date&);

  void RemoveRow(const Passport&, const CarSpec&, const FullName&,
                 const Date&);

  friend class MainWindow;

 private:
  inline static int kColumnWidth = 100;
  HashTable hashtable_;
  std::vector<RBTreeNode> data_;
  
  void draw_cell(TableContext, int, int, int, int, int, int) override;
};

inline void MainTable::InsertRow(const Passport& passport, const CarSpec& carspec, 
                                 const FullName& fullname, const Date& date) {
  // -1 means that this row was inserted while app is working,
  // so it mustn't make sense like -1 it this case
  int res = hashtable_.Insert(passport, carspec, fullname, date, -1);
  if (res == 0) {
    data_ = hashtable_.GetAllNodes();
    int number_of_rows = rows();
    rows(number_of_rows + 1);
    redraw(); 
  }
}

inline void MainTable::RemoveRow(const Passport& passport, const CarSpec& carspec,
                                 const FullName& fullname, const Date& date) {
  int res = hashtable_.Erase(passport, carspec, fullname, date);
  if (res == 0) {
    data_ = hashtable_.GetAllNodes();
    int number_of_rows = rows();
    rows(number_of_rows - 1);
    redraw(); 
  }
}

#endif // HANDBOOK_MAIN_TABLE_H_
