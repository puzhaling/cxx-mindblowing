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
          [this, &team_name] // syntax sugar for generating 
          // compiler specific functional object
              (const person_t &employee)
          {
            return team_name_for(employee) ==
                   team_name;
          }
}
