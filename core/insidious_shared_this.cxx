#include <vector>
#include <memory>

class Widget;

std:vector<std::shared_ptr<Widget>> processedWidgets;

class Widget {
public:

  // ...

  void process() {
    processedWidgets.emplace_back(this);
  }

  // ...
};

// code problem: when shared_ptr constructor takes raw pointer
// it creates control block for object, that is pointer by this
// raw pointer, so this code is not this dangerous until you don't
// have another shared_ptr's that points to the same Widget object
// (if so, you have a free ticket to the train of undefined behaviour,
//  because same object points by two non connected shared_ptr's
//  have multiple reference counter and, therefore, will be deallocated
//  minimum twice :) )



