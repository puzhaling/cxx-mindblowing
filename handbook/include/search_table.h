#ifndef HANDBOOK_SEARCH_TABLE_H_
#define HANDBOOK_SEARCH_TABLE_H

#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Table_Row.H>
#include <FL/fl_draw.H>  

#include "hashtable.h"

class SearchTable : public Fl_Table_Row {
 public:
  SearchTable(int x, int y, int w, int h, const char* title); 

  void InsertRow(const Passport&, const CarSpec&, const FullName&,
                 const Date&);

  void RemoveRow(const Passport&, const CarSpec&, const FullName&,
                 const Date&);

  void PopulateWith(const std::vector<std::pair<RBTreeNode, int>>&);

  friend class SearchWindow;

 private:
  inline static int kColumnWidth = 100;
  HashTable hashtable_;
  std::vector<std::pair<RBTreeNode, int>> data_;
  
  void draw_cell(TableContext, int, int, int, int, int, int) override;
};

inline void SearchTable::InsertRow(const Passport& passport, const CarSpec& carspec, 
                                   const FullName& fullname, const Date& date) {
  // -1 means that this row was inserted while app is working,
  // so it mustn't make sense like -1 it this case
  int res = hashtable_.Insert(passport, carspec, fullname, date, -1);
  if (res == 0) {
    data_.clear();
    hashtable_.FindAll(passport, carspec, date, data_);
    int number_of_rows = rows();
    rows(number_of_rows + 1);
    redraw(); 
  }
}

inline void SearchTable::RemoveRow(const Passport& passport, const CarSpec& carspec,
                                   const FullName& fullname, const Date& date) {
  int res = hashtable_.Erase(passport, carspec, fullname, date);
  if (res == 0) {
    data_.clear();
    hashtable_.FindAll(passport, carspec, date, data_);
    int number_of_rows = rows();
    rows(number_of_rows - 1);
    redraw(); 
  }
}

#endif // HANDBOOK_SEARCH_TABLE_H_
