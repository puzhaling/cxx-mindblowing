#include <vector>

std::vector<bool> features();

int main()
{
  /*
   * since vector<bool> uses proxy class vector<bool>::reference
   * auto type deduction leads to problems that depends on this class
   * realization. if this proxy class is implemented via pointer to
   * machine word in rvalue returned vector and offset in this word, then
   * type deduction leads to dangling pointer and, as a consequence,
   * to undefined behaviour. in contrast, explicit type declaration
   * uses implicit type inference (vector<bool>::reference -> bool)
   * to provide a correct type
   */
  bool highPriority = features(w)[5];
  // auto _highPriority = features(w)[5];
}
