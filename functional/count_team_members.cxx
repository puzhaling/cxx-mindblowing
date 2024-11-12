#include <string>
#include <vector>
#include <algorithm>

class company_t {
public:
  std::string team_name_for(const person_t &employee) const;

  int count_team_members(const std::string &team_name) const;

private:
  std::vector<person_t> m_employees;
};

int company_t::count_team_members(
        const std::string &team_name) const
{
  return std::count_if(
          m_employees.cbegin(), m_employees.cend(),
            // use explicit this ptr capture (only in non-static member
            // functions to access member variables and member functions
            // inside lamda's body
            // (use explicit capture to not get into trouble
            //  with unexpected results)
          [this, &team_name]
              (const person_t &employee)
          {
            return team_name_for(employee) ==
                   team_name;
          }
      );
}
