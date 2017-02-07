#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include "nameserverinterface.h"

class HNS : public NameServerInterface {
 public:
  HNS(int);
  virtual bool remove(const HostName&);
  virtual void insert(const HostName&, const IPAddress&);
  virtual IPAddress lookup(const HostName&) const;

 private:
  int nbr_of_elements;
  std::vector<std::vector<std::pair<HostName, IPAddress>>> db;
  std::hash<HostName> hasher;
};
