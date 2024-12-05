#include <variant>

template <typename... Ts>  // add operator() of all the types to
// our namespace
struct overloaded : Ts... { using Ts::operator()...; };

// pre c++17 deduction guide
template <typename... Ts> overloaded(Ts...) -> overloaded<Ts...>;


void point_for(player which_player)
{
  std::visit(
	     // thanks to overload resolution
	     // appropriate will be called
	     overloaded {
	       [&](const normal_scoring& state) {

	       },[&](const forty_scoring& state) {

	       },[&](const deuce& state) {

	       },[&](const advantage& state) {

	       }
		 },
	     m_state);
}
