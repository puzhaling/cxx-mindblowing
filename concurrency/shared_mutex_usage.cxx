#include <map>
#include <string>
#include <mutex>
#include <shared_mutex>

class dns_entry;

class dns_cache
{
  std::map<std::string, dns_entry> entries;
  mutable std::shared_mutex entry_mutex;

 public:
  // shared_mutex
  dns_entry find_entry(std::string const& domain) const
  {
    // 1st type of usage: concurrent access for multiple threads
    std::shared_lock<std::shared_mutex> lk(entry_mutex);
    std::map<std::string,dns_entry>::const_iterator const it =
        entries.find(domain);
    return (it == entries.end()) ? dns_entry() : it->second;
  }
  void update_or_add_entry(std::string const& domain,
                           dns_entry const& dns_details)
  {
    // 2nd type of usage: exclusive access for single thread
    std::lock_guard<std::shared_mutex> lk(entry_mutex);
    entries[domain] = dns_details;
  }
};
